#include <ndl.h>
#include <stdio.h> 
#include <assert.h>
#include <stdlib.h>

struct BitmapHeader {
  uint16_t type;
  uint32_t filesize;
  uint32_t resv_1;
  uint32_t offset;
  uint32_t ih_size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bitcount; // 1, 4, 8, or 24
  uint32_t compression;
  uint32_t sizeimg;
  uint32_t xres, yres;
  uint32_t clrused, clrimportant;
} __attribute__((packed));

int NDL_LoadBitmap(NDL_Bitmap *bmp, const char *filename) {
  FILE *fp;
  int w = 0, h = 0;
  uint32_t *pixels = NULL;

  w = h = 0;
  if (!(fp = fopen(filename, "r"))) return -1;

  struct BitmapHeader hdr;
  assert(sizeof(hdr) == 54);
  assert(1 == fread(&hdr, sizeof(struct BitmapHeader), 1, fp));

  if (hdr.bitcount != 24) return -1;
  if (hdr.compression != 0) return -1;
  pixels = (uint32_t*)malloc(hdr.width * hdr.height * sizeof(uint32_t));
  if (!pixels) return -1;

  w = hdr.width; h = hdr.height;
  int line_off = (w * 3 + 3) & ~0x3;

  for (int i = 0; i < h; i ++) {
    fseek(fp, hdr.offset + (h - 1 - i) * line_off, SEEK_SET);
    int nread = fread(&pixels[w * i], 3, w, fp);
    for (int j = w - 1; j >= 0; j --) {
      uint8_t b = *(((uint8_t*)&pixels[w * i]) + 3 * j);
      uint8_t g = *(((uint8_t*)&pixels[w * i]) + 3 * j + 1);
      uint8_t r = *(((uint8_t*)&pixels[w * i]) + 3 * j + 2);
      pixels[w * i + j] = (r << 16) | (g << 8) | b;
    }
  }

  fclose(fp);
  bmp->w = w;
  bmp->h = h;
  bmp->pixels = pixels;
  return 0;
}

int NDL_ReleaseBitmap(NDL_Bitmap *bmp) {
  assert(bmp->pixels);
  free(bmp->pixels);
  bmp->pixels = NULL;
}
