#ifndef BMP_H_
#define BMP_H_
#include <stdio.h>

typedef struct bmp_image {
  char*** pixels;
  int width;
  int height;
} bmp_img_t;

int load_bmp(FILE* file, bmp_img_t* img);
void crop(bmp_img_t* img, bmp_img_t* cropped_img, int x, int y, int width, int height);
void rotate(bmp_img_t* img, bmp_img_t* rotated_img);
void free_bmp_img(bmp_img_t* img);
void apply(void (op) (char* pixels), bmp_img_t img);
void save_bmp(FILE* from_file, bmp_img_t from_bmp, FILE* to_file);

#endif