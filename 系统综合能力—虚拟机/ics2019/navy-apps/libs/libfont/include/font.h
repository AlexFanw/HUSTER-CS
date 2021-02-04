#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>

class Font {
private:
  int w1, h1;
  void create(uint32_t ch, int *bbx, uint32_t *bitmap, int count);

public:
  const char *name;
  int w, h;
  uint32_t *font[256];

  Font(const char *filename);
  ~Font();
};

#endif
