#include <amtest.h>
#include <amdev.h>

static void input_test() {
  printf("Input device test skipped.\n");
}

static void timer_test() {
  _DEV_TIMER_UPTIME_t uptime;
  uint32_t t0, t1;

  _io_read(_DEV_TIMER, _DEVREG_TIMER_UPTIME, &uptime, sizeof(uptime));
  t0 = uptime.lo;

  for (int volatile i = 0; i < 10000000; i ++) ;

  _io_read(_DEV_TIMER, _DEVREG_TIMER_UPTIME, &uptime, sizeof(uptime));
  t1 = uptime.lo;

  printf("Loop 10^7 time elapse: %d ms\n", t1 - t0);
}

static void video_test() {
  _DEV_VIDEO_INFO_t info;
  _io_read(_DEV_VIDEO, _DEVREG_VIDEO_INFO, &info, sizeof(info));
  printf("Screen size: %d x %d\n", info.width, info.height);
  for (int x = 0; x < 100; x++)
    for (int y = 0; y < 100; y++) {
      _DEV_VIDEO_FBCTL_t ctl;
      uint32_t pixel = 0x006a005f;
      ctl.x = info.width / 2 - 50 + x;
      ctl.y = info.height / 2 - 50 + y;
      ctl.w = ctl.h = 1;
      ctl.sync = 1;
      ctl.pixels = &pixel;
      _io_write(_DEV_VIDEO, _DEVREG_VIDEO_FBCTL, &ctl, sizeof(ctl));
    }
  printf("You should see a purple square on the screen.\n");
}

static uint32_t pci_conf_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  uint32_t res;
  int nread = _io_read(_DEV_PCICONF, _DEVREG_PCICONF(bus, slot, func, offset), &res, 4);
  return (nread == 0) ? 0xffffffff : res;
}

static void pciconf_test() {
  for (int bus = 0; bus < 256; bus ++)
    for (int slot = 0; slot < 32; slot ++) {
      uint32_t info = pci_conf_read(bus, slot, 0, 0);
      uint16_t id = info >> 16, vendor = info & 0xffff;
      if (vendor != 0xffff) {
        printf("Get device %d:%d, id %x vendor %x", bus, slot, id, vendor);
        if (id == 0x100e && vendor == 0x8086) {
          printf(" <-- This is an Intel e1000 NIC card!");
        }
        printf("\n");
      }
    }
}

uint32_t devices[] = {
  _DEV_INPUT, _DEV_TIMER, _DEV_VIDEO, _DEV_PCICONF,
};

void devscan() {
  printf("_heap = [%08x, %08x)\n", _heap.start, _heap.end);
  input_test();
  timer_test();
  video_test();
  pciconf_test();
  printf("Test End!\n");
  while (1);
}
