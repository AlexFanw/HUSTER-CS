#include "ppu.h"
#include "cpu.h"
#include "fce.h"
#include "memory.h"
#include <klib.h>

//#define PROFILE
//#define HAS_US_TIMER

PPU_STATE ppu;

static bool ppu_2007_first_read;
static byte ppu_addr_latch;
static byte PPU_SPRRAM[0x100];
static byte PPU_RAM[0x4000];
static bool ppu_sprite_hit_occured = false;
static byte ppu_latch;

// PPU Constants
static const word ppu_base_nametable_addresses[4] = { 0x2000, 0x2400, 0x2800, 0x2C00 };

// For sprite-0-hit checks
static byte ppu_screen_background[264][248];

// Precalculated tile high and low bytes addition for pattern tables
static byte ppu_l_h_addition_table[256][256][8];
static byte ppu_l_h_addition_flip_table[256][256][8];


// PPUCTRL Functions

word ppu_base_nametable_address()           { return ppu_base_nametable_addresses[ppu.PPUCTRL & 0x3];  }
byte ppu_vram_address_increment()           { return common_bit_set(ppu.PPUCTRL, 2) ? 32 : 1;          }
word ppu_sprite_pattern_table_address()     { return common_bit_set(ppu.PPUCTRL, 3) ? 0x1000 : 0x0000; }
word ppu_background_pattern_table_address() { return common_bit_set(ppu.PPUCTRL, 4) ? 0x1000 : 0x0000; }
byte ppu_sprite_height()                    { return common_bit_set(ppu.PPUCTRL, 5) ? 16 : 8;          }
bool ppu_generates_nmi()                    { return common_bit_set(ppu.PPUCTRL, 7);                   }

// PPUMASK Functions

bool ppu_renders_grayscale()                { return common_bit_set(ppu.PPUMASK, 0); }
bool ppu_shows_background_in_leftmost_8px() { return common_bit_set(ppu.PPUMASK, 1); }
bool ppu_shows_sprites_in_leftmost_8px()    { return common_bit_set(ppu.PPUMASK, 2); }
bool ppu_shows_background()                 { return common_bit_set(ppu.PPUMASK, 3); }
bool ppu_shows_sprites()                    { return common_bit_set(ppu.PPUMASK, 4); }
bool ppu_intensifies_reds()                 { return common_bit_set(ppu.PPUMASK, 5); }
bool ppu_intensifies_greens()               { return common_bit_set(ppu.PPUMASK, 6); }
bool ppu_intensifies_blues()                { return common_bit_set(ppu.PPUMASK, 7); }

void ppu_set_renders_grayscale(bool yesno)                { common_modify_bitb(&ppu.PPUMASK, 0, yesno); }
void ppu_set_shows_background_in_leftmost_8px(bool yesno) { common_modify_bitb(&ppu.PPUMASK, 1, yesno); }
void ppu_set_shows_sprites_in_leftmost_8px(bool yesno)    { common_modify_bitb(&ppu.PPUMASK, 2, yesno); }
void ppu_set_shows_background(bool yesno)                 { common_modify_bitb(&ppu.PPUMASK, 3, yesno); }
void ppu_set_shows_sprites(bool yesno)                    { common_modify_bitb(&ppu.PPUMASK, 4, yesno); }
void ppu_set_intensifies_reds(bool yesno)                 { common_modify_bitb(&ppu.PPUMASK, 5, yesno); }
void ppu_set_intensifies_greens(bool yesno)               { common_modify_bitb(&ppu.PPUMASK, 6, yesno); }
void ppu_set_intensifies_blues(bool yesno)                { common_modify_bitb(&ppu.PPUMASK, 7, yesno); }

// PPUSTATUS Functions

bool ppu_sprite_overflow()               { return common_bit_set(ppu.PPUSTATUS, 5); }
bool ppu_sprite_0_hit()                  { return common_bit_set(ppu.PPUSTATUS, 6); }
bool ppu_in_vblank()                     { return common_bit_set(ppu.PPUSTATUS, 7); }

void ppu_set_sprite_overflow(bool yesno) { common_modify_bitb(&ppu.PPUSTATUS, 5, yesno); }
void ppu_set_sprite_0_hit(bool yesno)    { common_modify_bitb(&ppu.PPUSTATUS, 6, yesno); }
void ppu_set_in_vblank(bool yesno)       { common_modify_bitb(&ppu.PPUSTATUS, 7, yesno); }


// RAM

word ppu_get_real_ram_address(word address) {
  if (address < 0x2000) { return address; }
  else if (address < 0x3F00) {
    if (address < 0x3000) { return address; }
    else { return address; }
  }
  else if (address < 0x4000) {
    address = 0x3F00 | (address & 0x1F);
    if (address == 0x3F10 || address == 0x3F14 || address == 0x3F18 || address == 0x3F1C)
      address -= 0x10;
    return address;
  }
  return 0xFFFF;
}

byte ppu_ram_read(word address) {
  return PPU_RAM[ppu_get_real_ram_address(address)];
}

void ppu_ram_write(word address, byte data) {
  PPU_RAM[ppu_get_real_ram_address(address)] = data;
}

// 3F01 = 0F (00001111)
// 3F02 = 2A (00101010)
// 3F03 = 09 (00001001)
// 3F04 = 07 (00000111)
// 3F05 = 0F (00001111)
// 3F06 = 30 (00110000)
// 3F07 = 27 (00100111)
// 3F08 = 15 (00010101)
// 3F09 = 0F (00001111)
// 3F0A = 30 (00110000)
// 3F0B = 02 (00000010)
// 3F0C = 21 (00100001)
// 3F0D = 0F (00001111)
// 3F0E = 30 (00110000)
// 3F0F = 00 (00000000)
// 3F11 = 0F (00001111)
// 3F12 = 16 (00010110)
// 3F13 = 12 (00010010)
// 3F14 = 37 (00110111)
// 3F15 = 0F (00001111)
// 3F16 = 12 (00010010)
// 3F17 = 16 (00010110)
// 3F18 = 37 (00110111)
// 3F19 = 0F (00001111)
// 3F1A = 17 (00010111)
// 3F1B = 11 (00010001)
// 3F1C = 35 (00110101)
// 3F1D = 0F (00001111)
// 3F1E = 17 (00010111)
// 3F1F = 11 (00010001)
// 3F20 = 2B (00101011)


// Rendering

void ppu_draw_background_scanline(bool mirror) {
  int tile_x;
  for (tile_x = ppu_shows_background_in_leftmost_8px() ? 0 : 1; tile_x < 32; tile_x ++) {
    // Skipping off-screen pixels
    if (((tile_x << 3) - ppu.PPUSCROLL_X + (mirror ? 256 : 0)) > 256)
      continue;

    int tile_y = ppu.scanline >> 3;
    int tile_index = ppu_ram_read(ppu_base_nametable_address() + tile_x + (tile_y << 5) + (mirror ? 0x400 : 0));
    word tile_address = ppu_background_pattern_table_address() + 16 * tile_index;

    int y_in_tile = ppu.scanline & 0x7;
    byte l = ppu_ram_read(tile_address + y_in_tile);
    byte h = ppu_ram_read(tile_address + y_in_tile + 8);

    int x;
    for (x = 0; x < 8; x ++) {
      byte color = ppu_l_h_addition_table[l][h][x];

      // Color 0 is transparent
      if (color != 0) {
        word attribute_address = (ppu_base_nametable_address() + (mirror ? 0x400 : 0) + 0x3C0 + (tile_x >> 2) + (ppu.scanline >> 5) * 8);
        bool top = (ppu.scanline % 32) < 16;
        bool left = (tile_x % 32 < 16);

        byte palette_attribute = ppu_ram_read(attribute_address);

        if (!top) { palette_attribute >>= 4; }
        if (!left) { palette_attribute >>= 2; }
        palette_attribute &= 3;

        word palette_address = 0x3F00 + (palette_attribute << 2);
        int idx = ppu_ram_read(palette_address + color);

        ppu_screen_background[(tile_x << 3) + x][ppu.scanline] = color;

        draw((tile_x << 3) + x - ppu.PPUSCROLL_X + (mirror ? 256 : 0), ppu.scanline + 1, idx); // bg
      }
    }
  }
}

void ppu_draw_sprite_scanline() {
  int scanline_sprite_count = 0;
  int n;
  for (n = 0; n < 0x100; n += 4) {
    byte sprite_x = PPU_SPRRAM[n + 3];
    byte sprite_y = PPU_SPRRAM[n];

    // Skip if sprite not on scanline
    if (sprite_y > ppu.scanline || sprite_y + ppu_sprite_height() < ppu.scanline)
      continue;

    scanline_sprite_count++;

    // PPU can't render > 8 sprites
    if (scanline_sprite_count > 8) {
      ppu_set_sprite_overflow(true);
      // break;
    }

    bool vflip = PPU_SPRRAM[n + 2] & 0x80;
    bool hflip = PPU_SPRRAM[n + 2] & 0x40;

    word tile_address = ppu_sprite_pattern_table_address() + 16 * PPU_SPRRAM[n + 1];
    int y_in_tile = ppu.scanline & 0x7;
    byte l = ppu_ram_read(tile_address + (vflip ? (7 - y_in_tile) : y_in_tile));
    byte h = ppu_ram_read(tile_address + (vflip ? (7 - y_in_tile) : y_in_tile) + 8);

    byte palette_attribute = PPU_SPRRAM[n + 2] & 0x3;
    word palette_address = 0x3F10 + (palette_attribute << 2);
    int x;
    for (x = 0; x < 8; x ++) {
      int color = hflip ? ppu_l_h_addition_flip_table[l][h][x] : ppu_l_h_addition_table[l][h][x];

      // Color 0 is transparent
      if (color != 0) {
        int screen_x = sprite_x + x;
        int idx = ppu_ram_read(palette_address + color);

        // FIXME: we do not distinguish bbg and fg here to improve performance
        if (PPU_SPRRAM[n + 2] & 0x20) {
          draw(screen_x, sprite_y + y_in_tile + 1, idx); // bbg
        }
        else {
          draw(screen_x, sprite_y + y_in_tile + 1, idx); // fg
        }

        // Checking sprite 0 hit
        if (ppu_shows_background() && !ppu_sprite_hit_occured && n == 0 && ppu_screen_background[screen_x][sprite_y + y_in_tile] == color) {
          ppu_set_sprite_0_hit(true);
          ppu_sprite_hit_occured = true;
        }
      }
    }
  }
}

// PPU Lifecycle

void ppu_run(int cycles) {
  while (cycles-- > 0) { ppu_cycle(); }
}

static uint32_t background_time, sprite_time, cpu_time;
#ifdef PROFILE
#ifdef HAS_US_TIMER
# define TIMER_UNIT "us"
# define time_read(x) read_us(&x)
# define time_diff(t1, t0) us_timediff(&t1, &t0)
# define TIME_TYPE amtime
#else
# define TIMER_UNIT "ms"
# define time_read(x) x = uptime()
# define time_diff(t1, t0) (t1 - t0)
# define TIME_TYPE uint32_t
#endif
#else
# define time_read(x)
# define time_diff(t1, t0) 0
#endif

void ppu_cycle() {
#ifdef PROFILE
  TIME_TYPE t0, t1, t2, t3, t4, t5;
#endif

  if (!ppu.ready && cpu_clock() > 29658)
    ppu.ready = true;

  time_read(t0);
  cpu_run(256);
  time_read(t1);

  ppu.scanline++;

  if (ppu.scanline < H && ppu_shows_background()) {
    ppu_draw_background_scanline(false);
    ppu_draw_background_scanline(true);
  }

  time_read(t2);
  cpu_run(85 - 16);
  time_read(t3);

  if (ppu.scanline < H && ppu_shows_sprites()) {
    ppu_draw_sprite_scanline();
  }

  time_read(t4);
  cpu_run(16);
  time_read(t5);

  cpu_time += time_diff(t1, t0) + time_diff(t3, t2) + time_diff(t5, t4);
  background_time += time_diff(t2, t1);
  sprite_time += time_diff(t4, t3);

  if (ppu.scanline == 241) {
    ppu_set_in_vblank(true);
    ppu_set_sprite_0_hit(false);
    cpu_interrupt();
  }
  else if (ppu.scanline == 262) {
    ppu.scanline = -1;
    ppu_sprite_hit_occured = false;
    ppu_set_in_vblank(false);

    time_read(t0);
    fce_update_screen();
    time_read(t1);

#ifdef PROFILE
    uint32_t total = cpu_time + background_time + sprite_time + time_diff(t1, t0);
    printf("Time: cpu + bg + spr + scr = (%d + %d + %d + %d)\t= %d %s\n",
        cpu_time, background_time, sprite_time, time_diff(t1, t0), total, TIMER_UNIT);
#endif
    cpu_time = 0;
    background_time = 0;
    sprite_time = 0;
  }
}

void ppu_copy(word address, byte *source, int length) {
  memcpy(&PPU_RAM[address], source, length);
}

byte ppu_io_read(word address) {
  ppu.PPUADDR &= 0x3FFF;
  switch (address & 7) {
    case 2:
      {
        byte value = ppu.PPUSTATUS;
        ppu_set_in_vblank(false);
        ppu_set_sprite_0_hit(false);
        ppu.scroll_received_x = 0;
        ppu.PPUSCROLL = 0;
        ppu.addr_received_high_byte = 0;
        ppu_latch = value;
        ppu_addr_latch = 0;
        ppu_2007_first_read = true;
        return value;
      }
    case 4: return ppu_latch = PPU_SPRRAM[ppu.OAMADDR];
    case 7:
      {
        byte data;

        if (ppu.PPUADDR < 0x3F00) {
          data = ppu_latch = ppu_ram_read(ppu.PPUADDR);
        }
        else {
          data = ppu_ram_read(ppu.PPUADDR);
          ppu_latch = 0;
        }

        if (ppu_2007_first_read) {
          ppu_2007_first_read = false;
        }
        else {
          ppu.PPUADDR += ppu_vram_address_increment();
        }
        return data;
      }
    default: return 0xFF;
  }
}

void ppu_io_write(word address, byte data) {
  address &= 7;
  ppu_latch = data;
  ppu.PPUADDR &= 0x3FFF;
  switch(address) {
    case 0: if (ppu.ready) ppu.PPUCTRL = data; break;
    case 1: if (ppu.ready) ppu.PPUMASK = data; break;
    case 3: ppu.OAMADDR = data; break;
    case 4: PPU_SPRRAM[ppu.OAMADDR++] = data; break;
    case 5:
            {
              if (ppu.scroll_received_x)
                ppu.PPUSCROLL_Y = data;
              else
                ppu.PPUSCROLL_X = data;

              ppu.scroll_received_x ^= 1;
              break;
            }
    case 6:
            {
              if (!ppu.ready)
                return;

              if (ppu.addr_received_high_byte)
                ppu.PPUADDR = (ppu_addr_latch << 8) + data;
              else
                ppu_addr_latch = data;

              ppu.addr_received_high_byte ^= 1;
              ppu_2007_first_read = true;
              break;
            }
    case 7:
            {
              if (ppu.PPUADDR > 0x1FFF || ppu.PPUADDR < 0x4000) {
                ppu_ram_write(ppu.PPUADDR ^ ppu.mirroring_xor, data);
                ppu_ram_write(ppu.PPUADDR, data);
              }
              else {
                ppu_ram_write(ppu.PPUADDR, data);
              }
            }
  }
  ppu_latch = data;
}

void ppu_init() {
  ppu.PPUCTRL = ppu.PPUMASK = ppu.PPUSTATUS = ppu.OAMADDR = ppu.PPUSCROLL_X = ppu.PPUSCROLL_Y = ppu.PPUADDR = 0;
  ppu.PPUSTATUS |= 0xA0;
  ppu.PPUDATA = 0;
  ppu_2007_first_read = true;

  // Initializing low-high byte-pairs for pattern tables
  int h, l, x;
  for (h = 0; h < 0x100; h ++) {
    for (l = 0; l < 0x100; l ++) {
      for (x = 0; x < 8; x ++) {
        ppu_l_h_addition_table[l][h][x] = (((h >> (7 - x)) & 1) << 1) | ((l >> (7 - x)) & 1);
        ppu_l_h_addition_flip_table[l][h][x] = (((h >> x) & 1) << 1) | ((l >> x) & 1);
      }
    }
  }
}

void ppu_sprram_write(byte data) {
  PPU_SPRRAM[ppu.OAMADDR++] = data;
}

void ppu_set_background_color(byte color) {
}

void ppu_set_mirroring(byte mirroring) {
  ppu.mirroring = mirroring;
  ppu.mirroring_xor = 0x400 << mirroring;
}
