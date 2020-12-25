#ifndef BMP_H_
#define BMP_H_
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 2)

typedef struct bmp_header {
  struct {
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;
  } file_header;

  struct {
    uint32_t size;
    uint32_t width;
    uint32_t height;

    uint16_t planes;
    uint16_t bits_per_pixel;

    uint32_t compression;
    uint32_t image_size;

    uint32_t x_pixels_per_m;
    uint32_t y_pixels_per_m;

    uint32_t colors_used;
    uint32_t important_colors;
  } info_header;
} bmp_header_t;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct pixel {
  char b, g, r;
} pixel_t;

#pragma pack(pop)

typedef struct bmp_img {
  bmp_header_t header;
  pixel_t** pixels;
  int width;
  int height;
} bmp_img_t;

int load_bmp(FILE* file, bmp_img_t* img);
int crop(bmp_img_t* img, bmp_img_t* cropped_img, int x, int y, int width, int height);
int rotate(bmp_img_t* img, bmp_img_t* rotated_img);
void free_bmp_img(bmp_img_t* img);
void save_bmp(bmp_img_t* img, FILE* file);

#endif