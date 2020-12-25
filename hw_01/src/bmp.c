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
  fseek(bmp_file, 0x12, SEEK_SET); // width and height
  fread(&img->width, 4, 1, bmp_file);
  fread(&img->height, 4, 1, bmp_file);

  int pixels_pos;
  fseek(bmp_file, 0xA, SEEK_SET); // pixel data position in file
  fread(&pixels_pos, 4, 1, bmp_file);

  int pixels_size;
  fseek(bmp_file, 0x22, SEEK_SET); // size of pixel data in file
  fread(&pixels_size, 4, 1, bmp_file);

  int shift = get_shift(img->width); // for zero bytes skipping

  if (init_pixels(img) == -1)   
    return -1; 

  fseek(bmp_file, pixels_pos, SEEK_SET);
  for (int i = img->height - 1; i >= 0; i--) {
    if (fread(img->pixels[i], sizeof(pixel_t), img->width, bmp_file) != img->width)
      return -1;

    fseek(bmp_file, shift, SEEK_CUR); // skip zero bytes
  }

  return 0;
}

int crop(bmp_img_t* img, bmp_img_t* cropped_img, int x, int y, int width, int height) {
  cropped_img->width = width;
  cropped_img->height = height;
  if (init_pixels(cropped_img) == -1) 
    return -1;
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) 
      cropped_img->pixels[i][j] = img->pixels[y + i][x + j];
  return 0;
}

int rotate(bmp_img_t* img, bmp_img_t* rotated_img) {
  rotated_img->width = img->height;
  rotated_img->height = img->width;
  if (init_pixels(rotated_img) == -1) 
    return -1;
  for (int i = 0; i < rotated_img->height; i++)
    for (int j = 0; j < rotated_img->width; j++) 
      rotated_img->pixels[i][j] = img->pixels[img->height - 1 - j][i];
  return 0;
}

void save_bmp(FILE* from_file, bmp_img_t* from_bmp, FILE* to_file) {
  char buf[54];
  fseek(from_file, 0, SEEK_SET);
  fread(buf, 1, 54, from_file);
  fseek(to_file, 0, SEEK_SET);
  fwrite(buf, 1, 54, to_file);

  int shift = get_shift(from_bmp->width);
  int width_with_shift = from_bmp->width + shift;
  int size_pixel_data = (from_bmp->width * 3 + shift) * from_bmp->height;
  int size_file = size_pixel_data + 54;

  fseek(to_file, 0x2, SEEK_SET); // size of file
  fwrite(&size_file, sizeof(int), 1, to_file);

  fseek(to_file, 0x12, SEEK_SET); // width 
  fwrite(&from_bmp->width, sizeof(int), 1, to_file);

  fseek(to_file, 0x16, SEEK_SET); // height
  fwrite(&from_bmp->height, sizeof(int), 1, to_file);

  fseek(to_file, 0x22, SEEK_SET); // size of pixel data
  fwrite(&size_pixel_data, sizeof(int), 1, to_file);

  fseek(to_file, 54, SEEK_SET);
  for (int i = from_bmp->height - 1; i >= 0; i--) {

    fwrite(from_bmp->pixels[i], sizeof(pixel_t), from_bmp->width, to_file);

    for (int j = 0; j < shift; j++)
      putc('\0', to_file);
  }

}