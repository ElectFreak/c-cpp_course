#ifndef BMP_H_
#define BMP_H_
#include <stdio.h>

typedef struct pixel {
  char b, g, r;
} pixel_t;

typedef struct bmp_image {
  // char*** pixels;
  
  pixel_t** pixels;

  int width;
  int height;
} bmp_img_t;

int load_bmp(FILE* file, bmp_img_t* img);
int crop(bmp_img_t* img, bmp_img_t* cropped_img, int x, int y, int width, int height);
int rotate(bmp_img_t* img, bmp_img_t* rotated_img);
void free_bmp_img(bmp_img_t* img);
void save_bmp(FILE* from_file, bmp_img_t* from_bmp, FILE* to_file);

#endif