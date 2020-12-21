#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("No arguments\n");
    return 0;
  }

  if (strcmp(argv[1], "crop-rotate") == 0) {
    if (argc != 8) {
      printf("Invalid number of arguments\n");
      return 0;
    }

    FILE* in_bmp = fopen(argv[2], "rb");
    FILE* out_bmp = fopen(argv[3], "wb");
    if (in_bmp == NULL || out_bmp == NULL) {
      printf("Failed to open input/output file\n");
      return 0;
    }

    bmp_img_t img;
    if (load_bmp(in_bmp, &img) == -1) {
      printf("Failed to read bmp\n");
      return 0;
    }

    int x, y, w, h;
    x = atoi(argv[4]);
    y = atoi(argv[5]);
    w = atoi(argv[6]);
    h = atoi(argv[7]);

    if (x + w > img.width || y + h > img.height) {
      printf("Out of bounds img\n");
      return 0;
    }

    bmp_img_t cropped;
    crop(&img, &cropped, x, y, w, h);
    
    bmp_img_t rotated;
    rotate(&cropped, &rotated);
    save_bmp(in_bmp, rotated, out_bmp);

    free_bmp_img(&cropped);
    free_bmp_img(&rotated);
    free_bmp_img(&img);
  }

  
  return 0;
}