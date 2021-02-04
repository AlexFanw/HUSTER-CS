#ifndef __MAP_H__
#define __MAP_H__

#include "common.h"
#include "monitor/diff-test.h"

typedef void(*io_callback_t)(uint32_t, int, bool);
uint8_t* new_space(int size);

typedef struct {
  char *name;
  // we treat ioaddr_t as paddr_t here
  paddr_t low;
  paddr_t high;
  uint8_t *space;
  io_callback_t callback;
} IOMap;

static inline bool map_inside(IOMap *map, paddr_t addr) {
  return (addr >= map->low && addr <= map->high);
}

static inline int find_mapid_by_addr(IOMap *maps, int size, paddr_t addr) {
  int i;
  for (i = 0; i < size; i ++) {
    if (map_inside(maps + i, addr)) {
      difftest_skip_ref();
      return i;
    }
  }
  return -1;
}

void add_pio_map(char *name, ioaddr_t addr, uint8_t *space, int len, io_callback_t callback);
void add_mmio_map(char *name, paddr_t addr, uint8_t* space, int len, io_callback_t callback);

uint32_t map_read(paddr_t addr, int len, IOMap *map);
void map_write(paddr_t addr, uint32_t data, int len, IOMap *map);

#endif
