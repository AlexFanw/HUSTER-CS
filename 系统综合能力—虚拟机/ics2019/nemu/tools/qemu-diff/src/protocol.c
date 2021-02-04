/* Simple implementation of a GDB remote protocol client.
 * Copyright (C) 2015 Red Hat Inc.
 *
 * This file is part of gdb-toys.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common.h"
#include <ctype.h>
#include <err.h>
#include <stdbool.h>

#include <arpa/inet.h>

#include <netinet/in.h>
#include <netinet/tcp.h>

#include <sys/socket.h>
#include <sys/types.h>

struct gdb_conn {
  FILE *in;
  FILE *out;
  bool ack;
};


static uint8_t
hex_nibble(uint8_t hex) {
  return isdigit(hex) ? hex - '0' : tolower(hex) - 'a' + 10;
}

uint8_t hex_encode(uint8_t digit) {
  return digit > 9 ? 'a' + digit - 10 : '0' + digit;
}

uint16_t gdb_decode_hex(uint8_t msb, uint8_t lsb) {
  if (!isxdigit(msb) || !isxdigit(lsb))
    return UINT16_MAX;
  return 16 * hex_nibble(msb) + hex_nibble(lsb);
}

uint64_t gdb_decode_hex_str(uint8_t *bytes) {
  uint64_t value = 0;
  uint64_t weight = 1;
  while (isxdigit(bytes[0]) && isxdigit(bytes[1])) {
    value += weight * gdb_decode_hex(bytes[0], bytes[1]);
    bytes += 2;
    weight *= 16 * 16;
  }
  return value;
}


static struct gdb_conn* gdb_begin(int fd) {
  struct gdb_conn *conn = calloc(1, sizeof(struct gdb_conn *));
  if (conn == NULL)
    err(1, "calloc");

  conn->ack = true;

  // duplicate the handle to separate read/write state
  int fd2 = dup(fd);
  if (fd2 < 0)
    err(1, "dup");

  // open a FILE* for reading
  conn->in = fdopen(fd, "rb");
  if (conn->in == NULL)
    err(1, "fdopen");

  // open a FILE* for writing
  conn->out = fdopen(fd2, "wb");
  if (conn->out == NULL)
    err(1, "fdopen");

  // reset line state by acking any earlier input
  fputc('+', conn->out);
  fflush(conn->out);

  return conn;
}

struct gdb_conn* gdb_begin_inet(const char *addr, uint16_t port) {
  // fill the socket information
  struct sockaddr_in sa = {
    .sin_family = AF_INET,
    .sin_port = htons(port),
  };
  if (inet_aton(addr, &sa.sin_addr) == 0)
    errx(1, "Invalid address: %s", addr);

  // open the socket and start the tcp connection
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0)
    err(1, "socket");
  if (connect(fd, (const struct sockaddr *)&sa, sizeof(sa)) != 0) {
    close(fd);
    return NULL;
  }

  socklen_t tmp;
  tmp = 1;
  int r = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&tmp, sizeof(tmp));
  if (r) {
    perror("setsockopt");
    assert(0);
  }
  tmp = 1;
  r = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&tmp, sizeof(tmp));
  if (r) {
    perror("setsockopt");
    assert(0);
  }

  // initialize the rest of gdb on this handle
  return gdb_begin(fd);
}


void gdb_end(struct gdb_conn *conn) {
  fclose(conn->in);
  fclose(conn->out);
  free(conn);
}

static void send_packet(FILE *out, const uint8_t *command, size_t size) {
  // compute the checksum -- simple mod256 addition
  uint8_t sum = 0;
  size_t i;
  for (i = 0; i < size; ++i)
    sum += command[i];

  // NB: seems neither escaping nor RLE is generally expected by
  // gdbserver.  e.g. giving "invalid hex digit" on an RLE'd address.
  // So just write raw here, and maybe let higher levels escape/RLE.

  fputc('$', out); // packet start
  fwrite(command, 1, size, out); // payload
  fprintf(out, "#%02X", sum); // packet end, checksum
  fflush(out);

  if (ferror(out))
    err(1, "send");
  else if (feof(out))
    errx(0, "send: Connection closed");
}

void gdb_send(struct gdb_conn *conn, const uint8_t *command, size_t size) {
  bool acked = false;
  do {
    send_packet(conn->out, command, size);

    if (!conn->ack)
      break;

    // look for '+' ACK or '-' NACK/resend
    acked = fgetc(conn->in) == '+';
  } while (!acked);
}

static uint8_t* recv_packet(FILE *in, size_t *ret_size, bool* ret_sum_ok) {
  size_t i = 0;
  size_t size = 4096;
  uint8_t *reply = malloc(size);
  if (reply == NULL)
    err(1, "malloc");

  int c;
  uint8_t sum = 0;
  bool escape = false;

  // fast-forward to the first start of packet
  while ((c = fgetc(in)) != EOF && c != '$');

  while ((c = fgetc(in)) != EOF) {
    sum += c;
    switch (c) {
      case '$': // new packet?  start over...
        i = 0;
        sum = 0;
        escape = false;
        continue;

      case '#': // end of packet
        sum -= c; // not part of the checksum
        {
          uint8_t msb = fgetc(in);
          uint8_t lsb = fgetc(in);
          *ret_sum_ok = sum == gdb_decode_hex(msb, lsb);
        }
        *ret_size = i;

        // terminate it for good measure
        if (i == size) {
          reply = realloc(reply, size + 1);
          if (reply == NULL)
            err(1, "realloc");
        }
        reply[i] = '\0';

        return reply;

      case '}': // escape: next char is XOR 0x20
        escape = true;
        continue;

      case '*': // run-length-encoding
        // The next character tells how many times to repeat the last
        // character we saw.  The count is added to 29, so that the
        // minimum-beneficial RLE 3 is the first printable character ' '.
        // The count character can't be >126 or '$'/'#' packet markers.

        if (i > 0) { // need something to repeat!
          int c2 = fgetc(in);
          if (c2 < 29 || c2 > 126 || c2 == '$' || c2 == '#') {
            // invalid count character!
            ungetc(c2, in);
          } else {
            int count = c2 - 29;

            // get a bigger buffer if needed
            if (i + count > size) {
              size *= 2;
              reply = realloc(reply, size);
              if (reply == NULL)
                err(1, "realloc");
            }

            // fill the repeated character
            memset(&reply[i], reply[i - 1], count);
            i += count;
            sum += c2;
            continue;
          }
        }
    }

    // XOR an escaped character
    if (escape) {
      c ^= 0x20;
      escape = false;
    }

    // get a bigger buffer if needed
    if (i == size) {
      size *= 2;
      reply = realloc(reply, size);
      if (reply == NULL)
        err(1, "realloc");
    }

    // add one character
    reply[i++] = c;
  }

  if (ferror(in))
    err(1, "recv");
  else if (feof(in))
    errx(0, "recv: Connection closed");
  else
    errx(1, "recv: Unknown connection error");
}

uint8_t* gdb_recv(struct gdb_conn *conn, size_t *size) {
  uint8_t *reply;
  bool acked = false;
  do {
    reply = recv_packet(conn->in, size, &acked);

    if (!conn->ack)
      break;

    // send +/- depending on checksum result, retry if needed
    fputc(acked ? '+' : '-', conn->out);
    fflush(conn->out);
  } while (!acked);

  return reply;
}

const char* gdb_start_noack(struct gdb_conn *conn) {
  static const char cmd[] = "QStartNoAckMode";
  gdb_send(conn, (const uint8_t *)cmd, sizeof(cmd) - 1);

  size_t size;
  uint8_t *reply = gdb_recv(conn, &size);
  bool ok = size == 2 && !strcmp((const char*)reply, "OK");
  free(reply);

  if (ok)
    conn->ack = false;
  return ok ? "OK" : "";
}
