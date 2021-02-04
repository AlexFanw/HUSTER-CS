#include "common.h"
#include "device/map.h"

/* http://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming */

#define SERIAL_PORT 0x3F8
#define SERIAL_MMIO 0xa10003F8
#define CH_OFFSET 0

static uint8_t *serial_ch_base = NULL;

static void serial_ch_io_handler(uint32_t offset, int len, bool is_write) {
  assert(offset == 0);
  assert(is_write);
  assert(len == 1);

  char c = serial_ch_base[0];
  /* We bind the serial port with the host stdout in NEMU. */
  putc(c, stdout);
  if (c == '\n') {
    fflush(stdout);
  }
}

void init_serial() {
  serial_ch_base = new_space(1);
  add_pio_map("serial", SERIAL_PORT + CH_OFFSET, serial_ch_base, 1, serial_ch_io_handler);
  add_mmio_map("serial", SERIAL_MMIO + CH_OFFSET, serial_ch_base, 1, serial_ch_io_handler);
}
