#include <nwm.h>
#include <string.h>
#include <stdlib.h>

FILE *fbdev;

static void open_display();
static int W = -1, H = -1;

int main() {
  open_display();
  WindowManager *wm = new WindowManager(W, H);

  FILE *events = fopen("/dev/events", "r");

  while (1) {
    char buf[256];
    char *p = buf, ch;
    while ((ch = getc(events)) != -1) {
      *p ++ = ch;
      if (ch == '\n') break;
    }
    *p = 0;
    if (buf[0] != '\0') {
      wm->handle_event(buf);
    }
  }
  return 0;
}

static void open_display() {
  FILE *dispinfo = fopen("/proc/dispinfo", "r");

  if (!dispinfo) {
    fprintf(stderr, "Cannot open display information (/proc/dispinfo).\n");
    exit(1);
  }

  char buf[128], key[128], value[128], *delim;
  while (fgets(buf, 128, dispinfo)) {
    *(delim = strchr(buf, ':')) = '\0';
    sscanf(buf, "%s", key);
    sscanf(delim + 1, "%s", value);
    if (strcmp(key, "WIDTH") == 0) sscanf(value, "%d", &W);
    if (strcmp(key, "HEIGHT") == 0) sscanf(value, "%d", &H);
  }

  fclose(dispinfo);

  if (W == -1 || H == -1) {
    fprintf(stderr, "Invalid display information.\n");
    exit(1);
  }

  fbdev = fopen("/dev/fb", "w");
  if (!fbdev) {
    fprintf(stderr, "Cannot open display.\n");
    exit(1);
  }
}

