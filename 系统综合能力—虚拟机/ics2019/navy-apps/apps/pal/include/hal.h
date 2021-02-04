#ifndef __HAL_H__
#define __HAL_H__

#include "common.h"
#include <assert.h>

#define HZ 100

/* Unused macros in NEMU are defined to 0. */
#define SDL_VERSION_ATLEAST(x,y,z) 0
#define SDL_MUSTLOCK(surface) 0
#define SDL_RESIZABLE 0
#define SDL_FULLSCREEN 0
#define SDL_INIT_VIDEO 0
#define SDL_INIT_AUDIO 0
#define SDL_INIT_NOPARACHUTE 0
#define SDL_INIT_JOYSTICK 0

bool process_keys(void (*)(int), void (*)(int));

void incr_nr_draw(void);

typedef struct {
	int16_t x, y;
	uint16_t w, h;
} SDL_Rect;

typedef struct {
	uint8_t r, g, b, unused;
} SDL_Color;

typedef struct {
	int ncolors;
	SDL_Color *colors;
} SDL_Palette;

typedef struct {
	SDL_Palette *palette;
	uint8_t BitsPerPixel;
	uint8_t BytesPerPixel;
	uint8_t Rloss, Gloss, Bloss, Aloss;
	uint8_t Rshift, Gshift, Bshift, Ashift;
	uint32_t Rmask, Gmask, Bmask, Amask;
	uint32_t colorkey;
	uint8_t alpha;
} SDL_PixelFormat;

typedef struct {
	uint32_t flags;
	SDL_PixelFormat *format;
	int w, h;
	uint16_t pitch;
	SDL_Rect clip_rect;

	int refcount;
	uint8_t *pixels;

} SDL_Surface;

#define SDL_HWSURFACE 0x1
#define SDL_PHYSPAL 0x2
#define SDL_LOGPAL 0x4
#define SDL_SWSURFACE  0x8

typedef union {
	uint8_t type;
} SDL_Event;

#define K_UP		0x48
#define K_DOWN		0x50
#define K_LEFT		0x4b
#define K_RIGHT		0x4d
#define K_ESCAPE	0x01
#define K_RETURN	0x1c
#define K_SPACE		0x39
#define K_PAGEUP	0x49
#define K_PAGEDOWN	0x51
#define K_r			0x13
#define K_a			0x1e
#define K_d			0x20
#define K_e			0x12
#define K_w			0x11
#define K_q			0x10
#define K_s			0x1f
#define K_f			0x21
#define K_p			0x19


void SDL_BlitSurface(SDL_Surface *, SDL_Rect *, SDL_Surface *, SDL_Rect *);
uint32_t SDL_GetTicks();
void SDL_Delay(uint32_t ms);
SDL_Surface* SDL_CreateRGBSurface(uint32_t, int, int, int,
		uint32_t, uint32_t, uint32_t, uint32_t);
SDL_Surface* SDL_SetVideoMode(int, int, int, uint32_t);
void SDL_SetPalette(SDL_Surface *, int, SDL_Color *, int, int);
void SDL_FreeSurface(SDL_Surface *);
void SDL_SoftStretch(SDL_Surface *, SDL_Rect *, SDL_Surface *, SDL_Rect *);
void SDL_UpdateRect(SDL_Surface *, int, int, int, int);
void SDL_FillRect(SDL_Surface *, SDL_Rect *, uint32_t);

int SDL_PollEvent(SDL_Event *);
int SDL_LockSurface(SDL_Surface *);
void SDL_UnlockSurface(SDL_Surface *);
int SDL_ShowCursor(int);
int SDL_SaveBMP(SDL_Surface *, const char *);
int SDL_Init(uint32_t);
char *SDL_GetError(void);
void SDL_WM_SetCaption(const char *, const char *);
void SDL_Quit(void);

#endif

