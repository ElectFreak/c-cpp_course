#include <stdio.h>
#include <string.h>

#include "stego.h"
#include "bmp.h"

static char code(char sym) {
  if (sym == ',')
    return 27;
  if (sym == '.')
    return 28;
  return sym - 'A';
}

static char decode(char sym) {
  if (sym == 27)  
    return ',';
  if (sym == 28)
    return '.';
  return sym + 'A';
}

int get_key(FILE* file, int size, key_t* key) {
  for (int i = 0; i < size; i++)
    if (fscanf(file, "%d %d %c", &key[i].x, &key[i].y, (char*)&key[i].color) != 3)
      return -1;
  
  return 0;
}

void print_key(key_t* key, int size) {
  for (int i = 0; i < size; i++) {
    printf("x: %d, y: %d, color: %c\n", key[i].x, key[i].y, key[i].color);
  }
}

int insert(key_t* key, bmp_img_t* img, char* msg) {
  int len = strlen(msg); 
  for (int i = 0; i < len; i++) {
    char sym = code(msg[i]);
  
    for (int j = 0; j < 5; j++) {
      char mask = 1 & (sym >> j);

      int x = key[i * 5 + j].x;
      int y = key[i * 5 + j].y;
    
      if (x >= img->width || y >= img->height) {
        return -1;
      }

      if (key[i].color == r) {
        img->pixels[x][y].r = (img->pixels[x][y].r & (~1)) | mask;        
      }

      if (key[i].color == g) {
        img->pixels[x][y].g = (img->pixels[x][y].g & (~1)) | mask;
      }

      if (key[i].color == b) {
        img->pixels[x][y].b = (img->pixels[x][y].b & (~1)) | mask;
      }
    }
  }

  return 0;
}

int extract(key_t* key, bmp_img_t* img, char* msg, int len) {
  for (int i = 0; i < len; i++) {
    char sym = 0;

    for (int j = 0; j < 5; j++) {
      char mask;

      int x = key[i * 5 + j].x;
      int y = key[i * 5 + j].y;

      if (key[i].color == r) {
        mask = img->pixels[x][y].r & 1;
      }

      if (key[i].color == g) {
        mask = img->pixels[x][y].g & 1;
      }

      if (key[i].color == b) {
        mask = img->pixels[x][y].b & 1;
      }

      sym |= mask << j;
    }

    msg[i] = decode(sym);
  }
 
  return 0;
}