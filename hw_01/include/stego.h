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

int insert(key_t* key, bmp_img_t* img, char* msg);
int extract(key_t* key, bmp_img_t* img, char* msg, int len);
int get_key(FILE* file, int size, key_t* key);
void print_key(key_t* key, int size);

#endif