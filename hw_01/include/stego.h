#ifndef STEGO_H_
#define STEGO_H_

#include <stdio.h>

#include "bmp.h"

typedef enum color {
  r = 'R',
  g = 'G',
  b = 'B'
} color_t;

typedef struct key {
  int x, y;
  color_t color;
} key_t;

int insert(FILE* key_file, bmp_img_t* img, FILE* msg_file);
int extract(FILE* key_file, const bmp_img_t* img, FILE* msg_file);

#endif