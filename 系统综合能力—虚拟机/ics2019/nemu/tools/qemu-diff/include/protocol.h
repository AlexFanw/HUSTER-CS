/* Simple interface of a GDB remote protocol client.
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

#include <stdint.h>
#include "isa.h"

struct gdb_conn;

uint16_t gdb_decode_hex(uint8_t msb, uint8_t lsb);
uint64_t gdb_decode_hex_str(uint8_t *bytes);

uint8_t hex_encode(uint8_t digit);

struct gdb_conn *gdb_begin_inet(const char *addr, uint16_t port);

void gdb_end(struct gdb_conn *conn);

void gdb_send(struct gdb_conn *conn, const uint8_t *command, size_t size);

uint8_t *gdb_recv(struct gdb_conn *conn, size_t *size);

const char * gdb_start_noack(struct gdb_conn *conn);
