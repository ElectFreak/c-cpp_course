#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

static int init_pixels(bmp_img_t* img) {
  img->pixels = malloc(sizeof(pixel_t*) * img->height);
  if (img->pixels == NULL)
    return -1;
  
  pixel_t* buffer = malloc(sizeof(pixel_t) * img->width * img->height);
  if (buffer == NULL) {
    free (img->pixels);
    return -1;
  }

  for (int i = 0; i < img->height; i++) {
    img->pixels[i] = buffer + i * img->width;
  }

  return 0;
}

void free_bmp_img(bmp_img_t* img) {
  free(img->pixels[0]);
  free(img->pixels);
}

static int get_shift(int width) {
  return (4 - (width * 3) % 4) % 4;
}

int load_bmp(FILE* bmp_file, bmp_img_t* img) {
  fseek(bmp_file, 0, SEEK_SET);
  fread(&img->header, sizeof(bmp_header_t), 1, bmp_file);
  img->width = img->header.info_header.width;
  img->height = img->header.info_header.height;

  int shift = get_shift(img->width); // for zero bytes skipping

  if (init_pixels(img) == -1)   
    return -1; 

  fseek(bmp_file, img->header.file_header.data_offset, SEEK_SET);
  for (int i = img->height - 1; i >= 0; i--) {
    if (fread(img->pixels[i], sizeof(pixel_t), img->width, bmp_file) != img->width)
      return -1;

    fseek(bmp_file, shift, SEEK_CUR); // skip zero bytes
  }

  return 0;
}

int crop(bmp_img_t* img, bmp_img_t* cropped_img, int x, int y, int width, int height) {
  cropped_img->header = img->header;

  cropped_img->width = width;
  cropped_img->height = height;
  cropped_img->header.info_header.width = width;
  cropped_img->header.info_header.width = height;
  int image_size = (cropped_img->width * 3 + get_shift(cropped_img->width)) * cropped_img->height * 3;
  int file_size = 54 + image_size;

  cropped_img->header.info_header.image_size = image_size;
  cropped_img->header.file_header.file_size = file_size;

  if (init_pixels(cropped_img) == -1) 
    return -1;

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) 
      cropped_img->pixels[i][j] = img->pixels[y + i][x + j];
 
  return 0;
}

int rotate(bmp_img_t* img, bmp_img_t* rotated_img) {
  rotated_img->header = img->header;

  rotated_img->width = img->height;
  rotated_img->height = img->width;
  rotated_img->header.info_header.width = rotated_img->width;
  rotated_img->header.info_header.height = rotated_img->height;
  int image_size = (rotated_img->width * 3 + get_shift(rotated_img->width)) * rotated_img->height * 3;
  int file_size = 54 + image_size;

  rotated_img->header.info_header.image_size = image_size;
  rotated_img->header.file_header.file_size = file_size;

  if (init_pixels(rotated_img) == -1) 
    return -1;
    
  for (int i = 0; i < rotated_img->height; i++)
    for (int j = 0; j < rotated_img->width; j++) 
      rotated_img->pixels[i][j] = img->pixels[img->height - 1 - j][i];
  
  return 0;
}

void save_bmp(bmp_img_t* img, FILE* file) {
  fseek(file, 0, SEEK_SET);
  fwrite(&img->header, sizeof(bmp_header_t), 1, file);
 
  int shift = get_shift(img->width);
  for (int i = img->height - 1; i >= 0; i--) {
    fwrite(img->pixels[i], sizeof(pixel_t), img->width, file);
    for (int j = 0; j < shift; j++)
      putc('\0', file);
  }
}