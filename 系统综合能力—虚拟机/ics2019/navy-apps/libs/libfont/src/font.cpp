#include <font.h>
#include <stdio.h>
#include <string.h>

void Font::create(uint32_t ch, int *bbx, uint32_t *bitmap, int count) {
  font[ch] = new uint32_t[h];
  for (int y = 0; y < h; y ++) {
    uint32_t row = 0;
    for (int x = 0; x < w; x ++) {
      int x1 = x - bbx[2];
      int y1 = y - (h - bbx[1] - bbx[3]) - h1;
      if (x1 >= 0 && y1 >= 0 && y1 < bbx[1]) {
        uint32_t mask = bitmap[y1];
        if ( (mask >> (x1)) & 1 ) {
          row |= (1 << x);
        }
      }
    }
    font[ch][y] = row;
  }
}

Font::Font(const char *fname) {
  memset(font, 0, sizeof(font));
  FILE *fp = fopen(fname, "r");
  if (!fp) return;

  char buf[256], cmd[32];
  bool valid_file = false, in_bitmap = false;
  uint32_t bm[32], ch = '\0';
  int bm_idx, bm_bbx[4];

  while (fgets(buf, 256, fp)) {
    sscanf(buf, "%s ", cmd);
    if (strcmp(cmd, "STARTFONT") == 0) {
      valid_file = true;
    }
    if (strcmp(cmd, "FONTBOUNDINGBOX") == 0) {
      sscanf(buf, "%*s %d %d %d %d", &w, &h, &w1, &h1);
    }
    if (strcmp(cmd, "STARTCHAR") == 0) {
      sscanf(buf, "%*s %x", &ch);
    }
    if (strcmp(cmd, "BBX") == 0) {
      sscanf(buf, "%*s %d %d %d %d", &bm_bbx[0], &bm_bbx[1], &bm_bbx[2], &bm_bbx[3]);
    }
    if (strcmp(cmd, "ENDCHAR") == 0) {
      if (ch < 256) {
        create(ch, bm_bbx, bm, bm_idx);
      }
      in_bitmap = false;
      ch = '\0';
    } else if (strcmp(cmd, "BITMAP") == 0) {
      in_bitmap = true;
      bm_idx = 0;
    } else if (in_bitmap) {
      int idx = 0;
      bm[bm_idx] = 0;
      for (const char *p = buf; *p != '\n'; p ++) {
        int val;
        if (*p >= '0' && *p <= '9') val = *p - '0';
        else val = *p - 'A' + 10;
        for (int i = 0; i < 4; i ++) {
          if ((val >> (3 - i)) & 1) {
            bm[bm_idx] |= 1 << idx;
          }
          idx ++;
        }
      }
      bm_idx ++;
    }
    if (strcmp(cmd, "ENDFONT") == 0) {
      break;
    }
  }

  fclose(fp);
}

Font::~Font() {
  for (uint32_t *pixels: font) {
    if (pixels) delete [] pixels;
  }
}
