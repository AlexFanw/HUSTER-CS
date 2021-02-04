#include <am.h>
#include <klib.h>

extern uint32_t image[][400][300];
extern uint32_t image_end[][400][300];
#define NR_IMG (image_end - image)

void display_image(int i) {
  draw_rect(&image[i][0][0], 0, 0, 400, 300);
  draw_sync();
}

int main() {
  _ioe_init();
  
  int i = 0;
  unsigned long last = 0;
  unsigned long current;

  display_image(i);

  while (1) {
    current = uptime();
    if (current - last > 5000) {
      // change image every 5s
      i = (i + 1) % NR_IMG;
      display_image(i);
      last = current;
    }
  }
  return 0;
}
