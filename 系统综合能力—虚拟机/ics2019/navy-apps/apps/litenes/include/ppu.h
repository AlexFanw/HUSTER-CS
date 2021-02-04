#include "common.h"

#ifndef PPU_H
#define PPU_H

extern byte PPU_SPRRAM[0x100];
extern byte PPU_RAM[0x4000];

void ppu_init();
void ppu_finish();

byte ppu_ram_read(word address);
void ppu_ram_write(word address, byte data);
byte ppu_io_read(word address);
void ppu_io_write(word address, byte data);

bool ppu_generates_nmi();
void ppu_set_generates_nmi(bool yesno);

void ppu_set_mirroring(byte mirroring);

void ppu_run(int cycles);
void ppu_cycle();
int ppu_scanline();
void ppu_set_scanline(int s);
void ppu_copy(word address, byte *source, int length);
void ppu_sprram_write(byte data);

// PPUCTRL
bool ppu_shows_background();
bool ppu_shows_sprites();
bool ppu_in_vblank();
void ppu_set_in_vblank(bool yesno);

// PPU Memory and State
typedef struct {
    byte PPUCTRL;   // $2000 write only
    byte PPUMASK;   // $2001 write only
    byte PPUSTATUS; // $2002 read only
    byte OAMADDR;   // $2003 write only
    byte OAMDATA;   // $2004
	word PPUSCROLL;
    byte PPUSCROLL_X, PPUSCROLL_Y; // $2005 write only x2
    word PPUADDR;   // $2006 write only x2
    word PPUDATA;   // $2007

    bool scroll_received_x;
    bool addr_received_high_byte;
    bool ready;

    int mirroring, mirroring_xor;

    int x, scanline;
} PPU_STATE;

extern PPU_STATE ppu;
extern byte ppu_latch;
extern bool ppu_sprite_hit_occured;
extern byte ppu_screen_background[264][248];

word ppu_get_real_ram_address(word address);


// Screen State and Rendering

static inline byte ppu_l_h_addition(int h, int l, int x) {
  return (((h >> (7 - x)) & 1) << 1) | ((l >> (7 - x)) & 1);
}
static inline byte ppu_l_h_addition_flip(int l, int h, int x) {
  return (((h >> x) & 1) << 1) | ((l >> x) & 1);
}
 

// Draws current screen pixels in ppu_background_pixels & ppu_sprite_pixels and clears them
void ppu_render_screen();
void ppu_set_background_color(byte color);



// PPUCTRL Functions

word ppu_base_nametable_address();
byte ppu_vram_address_increment();
word ppu_sprite_pattern_table_address();
word ppu_background_pattern_table_address();
byte ppu_sprite_width();
byte ppu_sprite_height();
bool ppu_generates_nmi();



// PPUMASK Functions

bool ppu_renders_grayscale();
bool ppu_shows_background_in_leftmost_8px();
bool ppu_shows_sprites_in_leftmost_8px();
bool ppu_intensifies_reds();
bool ppu_intensifies_greens();
bool ppu_intensifies_blues();
void ppu_set_renders_grayscale(bool yesno);
void ppu_set_shows_background_in_leftmost_8px(bool yesno);
void ppu_set_shows_sprites_in_leftmost_8px(bool yesno);
void ppu_set_shows_background(bool yesno);
void ppu_set_shows_sprites(bool yesno);
void ppu_set_intensifies_reds(bool yesno);
void ppu_set_intensifies_greens(bool yesno);
void ppu_set_intensifies_blues(bool yesno);



// PPUSTATUS Functions

bool ppu_sprite_overflow();
bool ppu_sprite_0_hit();
bool ppu_in_vblank();

void ppu_set_sprite_overflow(bool yesno);
void ppu_set_sprite_0_hit(bool yesno);
void ppu_set_in_vblank(bool yesno);

#endif
