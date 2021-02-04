#include <fce.h>
#include <cpu.h>
#include <memory.h>
#include <ppu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ndl.h>

typedef struct {
  char signature[4];
  byte prg_block_count;
  byte chr_block_count;
  word rom_type;
  byte reserved[8];
} ines_header;

static ines_header *fce_rom_header;

static byte *romread(FILE *fp, int size) {
  byte *ret = malloc(size);
  if (fread(ret, 1, size, fp) != size) {
    fprintf(stderr, "Unexpected ending of ROM file.\n");
    exit(1);
  }
  return ret;
}

int fce_load_rom(const char *fname) {
  FILE *fp = fopen(fname, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open rom file.\n");
    return -1;
  }

  fce_rom_header = (ines_header*)romread(fp, sizeof(ines_header));

  if (0 != memcmp(fce_rom_header->signature, "NES\x1A", 4)) {
    fprintf(stderr, "Invalid NES rom.\n");
    return -1;
  }

  mmc_id = ((fce_rom_header->rom_type & 0xF0) >> 4);

  int prg_size = fce_rom_header->prg_block_count * 0x4000;
  
  byte *blk = romread(fp, prg_size);

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
    byte *blk = romread(fp, 0x2000);
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

static void frame() {
  int scanlines = 262;
  while (scanlines-- > 0) {
    ppu_run(1);
    cpu_run(1364 / 12); // 1 scanline
  }
}


extern int keydown[];
static int need_draw = false;

void fce_run() {
  int nframes = -1, cur = -1;

  NDL_OpenDisplay(W, H);

  while (1) {
    NDL_Event evt;
    NDL_WaitEvent(&evt);

    if (evt.type == NDL_EVENT_KEYUP || evt.type == NDL_EVENT_KEYDOWN) {
      int val = (evt.type == NDL_EVENT_KEYDOWN);
      //   p | 1 2      3     4  5    6    7     8
      // key | A B SELECT START UP DOWN LEFT RIGHT
      switch (evt.data) {
        case NDL_SCANCODE_ESCAPE: exit(0);
        case NDL_SCANCODE_W: keydown[5] = val; break;
        case NDL_SCANCODE_S: keydown[6] = val; break;
        case NDL_SCANCODE_A: keydown[7] = val; break;
        case NDL_SCANCODE_D: keydown[8] = val; break;
        case NDL_SCANCODE_T: keydown[3] = val; break;
        case NDL_SCANCODE_Y: keydown[4] = val; break;
        case NDL_SCANCODE_G: keydown[1] = val; break;
        case NDL_SCANCODE_H: keydown[2] = val; break;
      }
    }

    if (evt.type == NDL_EVENT_TIMER) {
      int uptime = evt.data;
      if (nframes == -1) {
        nframes = uptime / (1000 / FPS);
      }
      cur = uptime / (1000 / FPS);
      while (nframes < cur) {
        need_draw = (nframes + 1 == cur);
        frame();
        nframes ++;
      }
    }
  }
}

// Rendering

static const uint32_t palette[64] = {
  0x808080, 0x0000BB, 0x3700BF, 0x8400A6, 0xBB006A, 0xB7001E,
  0xB30000, 0x912600, 0x7B2B00, 0x003E00, 0x00480D, 0x003C22,
  0x002F66, 0x000000, 0x050505, 0x050505, 0xC8C8C8, 0x0059FF,
  0x443CFF, 0xB733CC, 0xFF33AA, 0xFF375E, 0xFF371A, 0xD54B00,
  0xC46200, 0x3C7B00, 0x1E8415, 0x009566, 0x0084C4, 0x111111,
  0x090909, 0x090909, 0xFFFFFF, 0x0095FF, 0x6F84FF, 0xD56FFF,
  0xFF77CC, 0xFF6F99, 0xFF7B59, 0xFF915F, 0xFFA233, 0xA6BF00,
  0x51D96A, 0x4DD5AE, 0x00D9FF, 0x666666, 0x0D0D0D, 0x0D0D0D,
  0xFFFFFF, 0x84BFFF, 0xBBBBFF, 0xD0BBFF, 0xFFBFEA, 0xFFBFCC,
  0xFFC4B7, 0xFFCCAE, 0xFFD9A2, 0xCCE199, 0xAEEEB7, 0xAAF7EE,
  0xB3EEFF, 0xDDDDDD, 0x111111, 0x111111
}; 

byte canvas[H][W];
uint32_t line[W];

void fce_update_screen() {
  if (!need_draw) {
    return;
  }
  static int frame = 0;
  frame ++;

  for (int y = 0; y < H; y ++) {
    if (y % 2 != frame % 2) continue;
    for (int x = 0; x < W; x ++) {
      line[x] = palette[canvas[y][x]];
    }
    NDL_DrawRect(line, 0, y, W, 1);
  }

  NDL_Render();

  int idx = ppu_ram_read(0x3F00);
  for (int y = 0; y < H; y ++)
    for (int x = 0; x < W; x ++)
      canvas[y][x] = idx;
}

void _ioe_init();

int main(int argc, char *argv[]) {
  const char *fname;
  if (argc < 2) {
    fname = "/share/games/nes/kungfu.nes";
    fprintf(stderr, "No ROM specified. Deafult to %s\n", fname);
  } else {
    fname = argv[1];
  }

  if (fce_load_rom(fname) == 0) {
    fce_init();
    fce_run();
  }

  return 1;
}

