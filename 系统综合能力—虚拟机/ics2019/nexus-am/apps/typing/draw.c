#include "game.h"

#define BACKGROUND_COLOR 0x2a0a29

//#define SCREEN_STRETCH

static uint32_t canvas[H][W];

static int last_draw_idx = 0;
static struct draw_info_t {
  int x, y;
} last_draw[1000];

extern char font8x8_basic[128][8];
static int x_adjust;
static int y_adjust;

static inline void draw_rect_adjust(uint32_t *pixels, int x, int y, int w, int h) {
  draw_rect(pixels, x + x_adjust, y + y_adjust, w, h);
}

void init_screen(void) {
  for (int y = 0; y < H; y ++)
    for (int x = 0; x < W; x ++)
      canvas[y][x] = BACKGROUND_COLOR;

  assert(screen_width() >= W);
  assert(screen_height() >= H);
  x_adjust = (screen_width() - W) / 2;
  y_adjust = (screen_height() - H) / 2;
  draw_rect_adjust(&canvas[0][0], 0, 0, W, H);
  draw_sync();
}

char *itoa(int n)  {  
  static char s[64];
  int i = sizeof(s) - 1;
  do {
    s[--i] = n % 10 + '0';  
    n /= 10;
  } while(n > 0);  
  return &s[i];
}

static inline void draw_character(char ch, int x, int y, int color) {
  int i, j;
  char *p = font8x8_basic[(int)ch];
  uint32_t buf[8][8];
  for (i = 0; i < 8; i ++)
    for (j = 0; j < 8; j ++) {
      assert(x + j < W && y + i < H);
      if ((p[i] >> j) & 1) {
        canvas[y + i][x + j] = color;
        buf[i][j] = color;
      }
      else {
        buf[i][j] = canvas[y + i][x + j];
      }
    }

  draw_rect_adjust(&buf[0][0], x, y, 8, 8);
  last_draw[last_draw_idx ++] = (struct draw_info_t){ .x = x, .y = y };
}

static inline void draw_string(const char *str, int x, int y, int color) {
  while (*str) {
    draw_character(*str ++, x, y, color);
    if (x + 8 >= W) {
      y += 8; x = 0;
    } else {
      x += 8;
    }
  }
}

static void clear_character(int x, int y) {
  int i, j;
  uint32_t buf[8][8];
  for (i = 0; i < 8; i ++)
    for (j = 0; j < 8; j ++) {
      assert(x + j < W && y + i < H);
      canvas[y + i][x + j] = BACKGROUND_COLOR;
      buf[i][j] = BACKGROUND_COLOR;
    }

  draw_rect_adjust(&buf[0][0], x, y, 8, 8);
}

static void clear_screen() {
  int i;
  for (i = 0; i < last_draw_idx; i ++) {
    clear_character(last_draw[i].x, last_draw[i].y);
  }
  last_draw_idx = 0;
}

void redraw_screen() {
  fly_t it;
  const char *hit, *miss;

  clear_screen();

  /* 绘制每个字符 */
  for (it = characters(); it != NULL; it = it->_next) {
    draw_character(it->text + 'A', it->x, it->y, 0xffffffff);
  }

  /* 绘制命中数、miss数、最后一次按键扫描码和fps */
  const char *key = itoa(last_key_code());
  draw_string(key, 0, H - 8, 0xffffffff);
  hit = itoa(get_hit());
  draw_string(hit, W - strlen(hit) * 8, 0, 0x00ff00);
  miss = itoa(get_miss());
  draw_string(miss, W - strlen(miss) * 8, H - 8, 0xfa5858);
  const char *fps = itoa(get_fps());
  draw_string(fps, 0, 0, 0xf3f781);
  draw_string("FPS", strlen(fps) * 8, 0, 0xf3f781);

#ifdef SCREEN_STRETCH
  assert(0);
  int w = screen_width();
  int h = screen_height();
  for (int x = 0; x < w; x ++)
    for (int y = 0; y < h; y ++) {
      draw_rect(&canvas[y * H / h][x * W / w], x, y, 1, 1);
    }
#endif

  draw_sync();
}
