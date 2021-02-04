#include "common.h"
#include "device/map.h"

#define PORT_IO_SPACE_MAX 65535

#define NR_MAP 8
static IOMap maps[NR_MAP] = {};
static int nr_map = 0;

/* device interface */
void add_pio_map(char *name, ioaddr_t addr, uint8_t *space, int len, io_callback_t callback) {
  assert(nr_map < NR_MAP);
  assert(addr + len <= PORT_IO_SPACE_MAX);
  maps[nr_map] = (IOMap){ .name = name, .low = addr, .high = addr + len - 1,
    .space = space, .callback = callback };
  Log("Add port-io map '%s' at [0x%08x, 0x%08x]", maps[nr_map].name, maps[nr_map].low, maps[nr_map].high);

  nr_map ++;
}

static inline uint32_t pio_read_common(ioaddr_t addr, int len) {
  assert(addr + len - 1 < PORT_IO_SPACE_MAX);
  int mapid = find_mapid_by_addr(maps, nr_map, addr);
  assert(mapid != -1);
  return map_read(addr, len, &maps[mapid]);
}

static inline void pio_write_common(ioaddr_t addr, uint32_t data, int len) {
  assert(addr + len - 1 < PORT_IO_SPACE_MAX);
  int mapid = find_mapid_by_addr(maps, nr_map, addr);
  assert(mapid != -1);
  map_write(addr, data, len, &maps[mapid]);
}

/* CPU interface */
uint32_t pio_read_l(ioaddr_t addr) { return pio_read_common(addr, 4); }
uint32_t pio_read_w(ioaddr_t addr) { return pio_read_common(addr, 2); }
uint32_t pio_read_b(ioaddr_t addr) { return pio_read_common(addr, 1); }
void pio_write_l(ioaddr_t addr, uint32_t data) { pio_write_common(addr, data, 4); }
void pio_write_w(ioaddr_t addr, uint32_t data) { pio_write_common(addr, data, 2); }
void pio_write_b(ioaddr_t addr, uint32_t data) { pio_write_common(addr, data, 1); }
