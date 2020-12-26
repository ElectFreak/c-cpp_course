#include <stdio.h>

#include "stego.h"
#include "bmp.h"

static char code(char sym) {
  if (sym == ' ')
    return 26;
  if (sym == '.')
    return 27;
  if (sym == ',')
    return 28;
  return sym - 'A';
}

static char decode(char sym) {
  if (sym == 26)
    return ' ';
  if (sym == 27)  
    return '.';
  if (sym == 28)
    return ',';
  return sym + 'A';
}

static int get_key(FILE* file, key_t* key) {
    if (fscanf(file, "%d %d %c", &key->x, &key->y, &key->color) != 3)
      return -1;
  
  return 0;
}

static void print_key(key_t* key) {
  printf("x: %d, y: %d, color: %d\n", key->x, key->y, (int)key->color);
}

int insert(FILE* key_file, bmp_img_t* img, FILE* msg_file) {
  while (1) {
    int chr = getc(msg_file);
    if (chr == EOF || chr == '\n') {
      break;
    }
    char coded_chr = code(chr);
  
    for (int j = 0; j < 5; j++) {
      key_t key; 
      if (get_key(key_file, &key) == -1)
        return -1;
      
      char mask = 1 & (coded_chr >> j);

      int x = key.x;
      int y = key.y;

      if (x >= img->width || y >= img->height) {
        return -1;
      }

      if (key.color == 'R') {
        img->pixels[y][x].r = (img->pixels[y][x].r & (~1)) | mask;        
      }

      if (key.color == 'G') {
        img->pixels[y][x].g = (img->pixels[y][x].g & (~1)) | mask;
      }

      if (key.color == 'B') {
        img->pixels[y][x].b = (img->pixels[y][x].b & (~1)) | mask;
      }
    }

  }

  return 0;
}

int extract(FILE* key_file, const bmp_img_t* img, FILE* msg_file) {
  key_t key;
  while (1) {
    char chr = 0;

    for (int j = 0; j < 5; j++) {
      char mask;
      
      if (get_key(key_file, &key) == -1) {
        putc('\n', msg_file);
        return 0;
      }
      
      int x = key.x;
      int y = key.y;

      if (x >= img->width || y >= img->height)
        return -1;

      if (key.color == 'R') {
        mask = img->pixels[y][x].r & 1;
      }

      if (key.color == 'G') {
        mask = img->pixels[y][x].g & 1;
      }

      if (key.color == 'B') {
        mask = img->pixels[y][x].b & 1;
      }

      chr |= mask << j;
    }

    putc(decode(chr), msg_file);
  }
 
  return 0;
}