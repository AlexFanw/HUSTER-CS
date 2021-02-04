#include <ndl.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static int has_nwm = 0;
static uint32_t *canvas;
static FILE *fbdev, *evtdev, *fbsyncdev;

static void get_display_info();
static int canvas_w, canvas_h, screen_w, screen_h, pad_x, pad_y;

int NDL_OpenDisplay(int w, int h) {
  if (!canvas) {
    NDL_CloseDisplay();
  }

  canvas_w = w;
  canvas_h = h;
  canvas = malloc(sizeof(uint32_t) * w * h);
  assert(canvas);

  if (getenv("NWM_APP")) {
    has_nwm = 1;
  } else {
    has_nwm = 0;
  }

  if (has_nwm) {
    printf("\033[X%d;%ds", w, h); fflush(stdout);
    evtdev = stdin;
  } else {
    get_display_info();
    assert(screen_w >= canvas_w);
    assert(screen_h >= canvas_h);
    pad_x = (screen_w - canvas_w) / 2;
    pad_y = (screen_h - canvas_h) / 2;
    fbdev = fopen("/dev/fb", "w"); assert(fbdev);
    evtdev = fopen("/dev/events", "r"); assert(evtdev);
    fbsyncdev = fopen("/dev/fbsync", "w"); assert(fbsyncdev);
  }
}

int NDL_CloseDisplay() {
  if (canvas) {
    free(canvas);
  }
  return 0;
}

int NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  if (has_nwm) {
    for (int i = 0; i < h; i ++) {
      printf("\033[X%d;%d", x, y + i);
      for (int j = 0; j < w; j ++) {
        putchar(';');
        fwrite(&pixels[i * w + j], 1, 4, stdout);
      }
      printf("d\n");
    }
  } else {
    for (int i = 0; i < h; i ++) {
      for (int j = 0; j < w; j ++) {
        canvas[(i + y) * canvas_w + (j + x)] = pixels[i * w + j];
      }
    }
  }
}

int NDL_Render() {
  if (has_nwm) {
    fflush(stdout);
  } else {
    for (int i = 0; i < canvas_h; i ++) {
      fseek(fbdev, ((i + pad_y) * screen_w + pad_x) * sizeof(uint32_t), SEEK_SET);
      fwrite(&canvas[i * canvas_w], sizeof(uint32_t), canvas_w, fbdev);
    }
    fflush(fbdev);
    putc(0, fbsyncdev);
    fflush(fbsyncdev);
  }
}

#define keyname(k) #k,

static const char *keys[] = {
  "NONE",
  _KEYS(keyname)
};

#define numkeys ( sizeof(keys) / sizeof(keys[0]) )

int NDL_WaitEvent(NDL_Event *event) {
  char buf[256], *p = buf, ch;

  while (1) {
    while ((ch = getc(evtdev)) != -1) {
      *p ++ = ch;
      assert(p - buf < sizeof(buf));
      if (ch == '\n') break;
    }

    if (buf[0] == 'k') {
      char keyname[32];
      event->type = buf[1] == 'd' ? NDL_EVENT_KEYDOWN : NDL_EVENT_KEYUP;
      event->data = -1;
      sscanf(buf + 3, "%s", keyname);
      for (int i = 0; i < numkeys; i ++) {
        if (strcmp(keys[i], keyname) == 0) {
          event->data = i;
          break;
        }
      }
      assert(event->data >= 1 && event->data < numkeys);
      return 0;
    }
    if (buf[0] == 't') {
      int tsc;
      sscanf(buf + 2, "%d", &tsc);
      event->type = NDL_EVENT_TIMER;
      event->data = tsc;
      return 0;
    }
  }

  assert(0);
  return -1;
}

static void get_display_info() {
  FILE *dispinfo = fopen("/proc/dispinfo", "r");
  assert(dispinfo);
  screen_w = screen_h = 0;
  char buf[128], key[128], value[128], *delim;
  while (fgets(buf, 128, dispinfo)) {
    *(delim = strchr(buf, ':')) = '\0';
    sscanf(buf, "%s", key);
    sscanf(delim + 1, "%s", value);
    if (strcmp(key, "WIDTH") == 0) sscanf(value, "%d", &screen_w);
    if (strcmp(key, "HEIGHT") == 0) sscanf(value, "%d", &screen_h);
  }
  fclose(dispinfo);
  assert(screen_w > 0 && screen_h > 0);
}

