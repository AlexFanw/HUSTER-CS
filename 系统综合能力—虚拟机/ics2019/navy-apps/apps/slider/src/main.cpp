#include <ndl.h>
#include <stdio.h>
#include <assert.h>

// USAGE: 
//   j/down - page down
//   k/up - page up
//   gg - first page

// number of slides
const int N = 19;
// slides path pattern (starts from 0)
const char *path = "/share/slides/slides-%d.bmp";
// slides size
const int W = 400, H = 300;

static NDL_Bitmap slide;
static int cur = 0;

void render() {
  if (slide.pixels) {
    NDL_ReleaseBitmap(&slide);
  }
  char fname[256];
  sprintf(fname, path, cur);
  assert(NDL_LoadBitmap(&slide, fname) == 0);
  NDL_DrawRect(slide.pixels, 0, 0, W, H);
  NDL_Render();
}

void prev(int rep) {
  if (rep == 0) rep = 1;
  cur -= rep;
  if (cur < 0) cur = 0;
  render();
}

void next(int rep) {
  if (rep == 0) rep = 1;
  cur += rep;
  if (cur >= N) cur = N - 1;
  render();
}

int main() {
  NDL_OpenDisplay(W, H);

  int rep = 0, g = 0;

  render();

  while (1) {
    NDL_Event e;
    NDL_WaitEvent(&e);

    if (e.type == NDL_EVENT_KEYDOWN) {
      switch(e.data) {
        case NDL_SCANCODE_0: rep = rep * 10 + 0; break;
        case NDL_SCANCODE_1: rep = rep * 10 + 1; break;
        case NDL_SCANCODE_2: rep = rep * 10 + 2; break;
        case NDL_SCANCODE_3: rep = rep * 10 + 3; break;
        case NDL_SCANCODE_4: rep = rep * 10 + 4; break;
        case NDL_SCANCODE_5: rep = rep * 10 + 5; break;
        case NDL_SCANCODE_6: rep = rep * 10 + 6; break;
        case NDL_SCANCODE_7: rep = rep * 10 + 7; break;
        case NDL_SCANCODE_8: rep = rep * 10 + 8; break;
        case NDL_SCANCODE_9: rep = rep * 10 + 9; break;
        case NDL_SCANCODE_J: 
        case NDL_SCANCODE_DOWN:
          next(rep);
          rep = 0; g = 0;
          break;
        case NDL_SCANCODE_K:
        case NDL_SCANCODE_UP:
          prev(rep);
          rep = 0; g = 0;
          break;
        case NDL_SCANCODE_G:
          g ++;
          if (g > 1) {
            prev(100000);
            rep = 0; g = 0;
          }
          break;
      }
    }
  }

  return 0;
}

