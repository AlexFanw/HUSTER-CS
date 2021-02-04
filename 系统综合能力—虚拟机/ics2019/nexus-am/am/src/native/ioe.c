#include <am.h>
#include <amdev.h>

void __am_timer_init();
void __am_video_init();
void __am_input_init();

size_t __am_input_read(uintptr_t reg, void *buf, size_t size);
size_t __am_timer_read(uintptr_t reg, void *buf, size_t size);
size_t __am_video_read(uintptr_t reg, void *buf, size_t size);
size_t __am_video_write(uintptr_t reg, void *buf, size_t size);

int _ioe_init() {
  __am_timer_init();
  __am_video_init();
  __am_input_init();
  return 0;
}

size_t _io_read(uint32_t dev, uintptr_t reg, void *buf, size_t size) {
  switch (dev) {
    case _DEV_INPUT: return __am_input_read(reg, buf, size);
    case _DEV_TIMER: return __am_timer_read(reg, buf, size);
    case _DEV_VIDEO: return __am_video_read(reg, buf, size);
  }
  return 0;
}

size_t _io_write(uint32_t dev, uintptr_t reg, void *buf, size_t size) {
  switch (dev) {
    case _DEV_VIDEO: return __am_video_write(reg, buf, size);
  }
  return 0;
}
