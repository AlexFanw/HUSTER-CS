#include <am.h>
#include <amdev.h>
#include <SDL2/SDL.h>

#define W 400
#define H 300
#define FPS 30

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static SDL_Texture *texture = NULL;
static uint32_t fb[W * H] = {};

static inline int min(int x, int y) {
  return (x < y) ? x : y;
}

static Uint32 texture_sync(Uint32 interval, void *param) {
  SDL_UpdateTexture(texture, NULL, fb, W * sizeof(Uint32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  return interval;
}

void __am_video_init() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  SDL_CreateWindowAndRenderer(W * 2, H * 2, 0, &window, &renderer);
  SDL_SetWindowTitle(window, "Native Application");
  texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
  memset(fb, 0, W * H * sizeof(uint32_t));
  SDL_AddTimer(1000 / FPS, texture_sync, NULL);
}

size_t __am_video_read(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_VIDEO_INFO: {
      _DEV_VIDEO_INFO_t *info = (_DEV_VIDEO_INFO_t *)buf;
      info->width = W;
      info->height = H;
      return sizeof(_DEV_VIDEO_INFO_t);
    }
  }
  return 0;
}

size_t __am_video_write(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_VIDEO_FBCTL: {
      _DEV_VIDEO_FBCTL_t *ctl = (_DEV_VIDEO_FBCTL_t *)buf;
      int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
      uint32_t *pixels = ctl->pixels;
      int cp_bytes = sizeof(uint32_t) * min(w, W - x);
      for (int j = 0; j < h && y + j < H; j ++) {
        memcpy(&fb[(y + j) * W + x], pixels, cp_bytes);
        pixels += w;
      }
      if (ctl->sync) {
        // do nothing, texture_sync() is called by SDL_timer
      }
      return size;
    }
  }
  return 0;
}
