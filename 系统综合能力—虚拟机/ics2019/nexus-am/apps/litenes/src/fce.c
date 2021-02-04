#include "fce.h"
#include "cpu.h"
#include "memory.h"
#include "ppu.h"
#include "psg.h"
#include <klib.h>
#include <amdev.h>

static int frame_cnt;
bool candraw() { return frame_cnt % 3 == 0; }

static uint32_t canvas[W * H];

void draw(int x, int y, int idx) {
  if (x >= 0 && x < W && y >= 0 && y < H && candraw()) {
    canvas[y * W + x] = palette[idx];
  }
}

typedef struct {
  char signature[4];
  byte prg_block_count;
  byte chr_block_count;
  word rom_type;
  byte reserved[8];
} ines_header;

static byte *buf;
static ines_header *fce_rom_header;

byte *romread(int size) {
  byte *ret = buf;
  buf += size;
  return ret;
}

int fce_load_rom(char *rom) {
  buf = (byte*)rom;
  fce_rom_header = (ines_header*)romread(sizeof(ines_header));

  if (memcmp(fce_rom_header->signature, "NES\x1A", 4)) {
    return -1;
  }

  mmc_id = ((fce_rom_header->rom_type & 0xF0) >> 4);

  int prg_size = fce_rom_header->prg_block_count * 0x4000;

  byte *blk = romread(prg_size);

  if (mmc_id == 0 || mmc_id == 3) {
    // if there is only one PRG block, we must repeat it twice
    if (fce_rom_header->prg_block_count == 1) {
      mmc_copy(0x8000, blk, 0x4000);
      mmc_copy(0xC000, blk, 0x4000);
    }
    else {
      mmc_copy(0x8000, blk, 0x8000);
    }
  }
  else {
    return -1;
  }

  // Copying CHR pages into MMC and PPU
  int i;
  for (i = 0; i < fce_rom_header->chr_block_count; i++) {
    byte *blk = romread(0x2000);
    mmc_append_chr_rom_page(blk);

    if (i == 0) {
      ppu_copy(0x0000, blk, 0x2000);
    }
  }

  return 0;
}

void fce_init() {
  cpu_init();
  ppu_init();
  ppu_set_mirroring(fce_rom_header->rom_type & 1);
  cpu_reset();
}

static unsigned long gtime;

void wait_for_frame() {
  unsigned long cur = uptime();
  while (cur - gtime < 1000 / FPS) {
    cur = uptime();
  }
  gtime = cur;
}

// FCE Lifecycle

void fce_run() {
  gtime = uptime();
  int nr_draw = 0;
  uint32_t last = gtime;
  while(1) {
    wait_for_frame();
    int scanlines = 262;

    while (scanlines-- > 0) {
      ppu_cycle();
      psg_detect_key();
    }

    nr_draw ++;
    if (uptime() - last > 1000) {
      last = uptime();
      printf("FPS = %d\n", nr_draw);
      nr_draw = 0;
    }
  }
}

void fce_update_screen() {
  frame_cnt ++;
  if (!candraw()) return;

  int idx = ppu_ram_read(0x3F00);
  uint32_t bgc = palette[idx];

  int w = screen_width();
  int h = screen_height();

  int xpad = (w - W) / 2;
  int ypad = (h - H) / 2;
  assert(xpad >= 0 && ypad >= 0);

  for (int x = 0; x < W; x ++) {
    for (int y = 0; y < H; y ++) {
      draw_rect(&canvas[y * W + x], xpad + x, ypad + y, 1, 1);
    }
  }

  draw_sync();

  for (int i = 0; i < W * H; i ++) canvas[i] = bgc;
}

#include "roms/gen/roms.h"

int main(const char *rom_name) {
  _ioe_init();

  struct rom *rom = &roms[0];
  for (int i = 1; i < nroms; i++) {
    struct rom *cur = &roms[i];
    if (strcmp(cur->name, rom_name) == 0) {
      rom = cur;
    }
  }

  printf("LiteNES ROM: %s\n", rom->name);

  fce_load_rom(rom->body);
  fce_init();
  printf("Initialization finish!\n");
  fce_run();
  return 1;
}
