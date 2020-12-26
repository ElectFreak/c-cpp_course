#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bmp.h"
#include "stego.h"

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
    if (in_bmp == NULL) {
      printf("Failed to open input file\n");

      return 0;
    }

    FILE* out_bmp = fopen(argv[3], "wb");
    if (out_bmp == NULL) {
      printf("Failed to open input/output file\n");
      fclose(in_bmp);

      return 0;
    }

    bmp_img_t img;
    if (load_bmp(in_bmp, &img) == -1) {
      printf("Failed to read bmp\n");
      fclose(in_bmp);
      fclose(out_bmp);

      return 0;
    }

    int x, y, w, h;
    x = atoi(argv[4]);
    y = atoi(argv[5]);
    w = atoi(argv[6]);
    h = atoi(argv[7]);

    if (x < 0 || y < 0 || x + w > img.width || y + h > img.height) {
      printf("Out of bounds img\n");
      free_bmp_img(&img);
      fclose(in_bmp);
      fclose(out_bmp);

      return 0;
    }

    bmp_img_t cropped;
    if (crop(&img, &cropped, x, y, w, h) == -1) {
      printf("Failed to crop img\n");
      free_bmp_img(&img);
      fclose(in_bmp);
      fclose(out_bmp);

      return 0;
    }
    
    bmp_img_t rotated;
    if (rotate(&cropped, &rotated) == -1) {
      printf("Failed to rotate img\n");
      free_bmp_img(&img);
      free_bmp_img(&cropped);
      fclose(in_bmp);
      fclose(out_bmp);

      return 0;
    }

    save_bmp(&rotated, out_bmp);

    free_bmp_img(&cropped);
    free_bmp_img(&rotated);
    free_bmp_img(&img);
    fclose(in_bmp);
    fclose(out_bmp);
  }

  if (strcmp(argv[1], "insert") == 0) {
    if (argc != 6) {
      printf("Invalid number of arguments\n");
      return 0;
    }

    FILE  *in_bmp = NULL,
          *out_bmp = NULL,
          *key_file = NULL,
          *msg_file = NULL;
    
    bmp_img_t img;

    in_bmp = fopen(argv[2], "rb");
    if (in_bmp == NULL) {
      printf("Failed to open input file\n");
      goto free_all;
    }

    out_bmp = fopen(argv[3], "wb");
    if (out_bmp == NULL) {
      printf("Failed to open output file\n");
      goto free_all;
    }

    key_file = fopen(argv[4], "r");
    if (key_file == NULL) {
      printf("Failed to open key file\n");
      goto free_all;
    }

    msg_file = fopen(argv[5], "r");
    if (msg_file == NULL) {
      printf("Failed to open message file\n");
      goto free_all;
    }  
        
    if (load_bmp(in_bmp, &img) == -1) {
      printf("Failed to load image\n");
      goto free_all;
    } 

    if (insert(key_file, &img, msg_file) == -1) {
      printf("Failed to insert key\n");
      goto free_all;
    }

    save_bmp(&img, out_bmp);

    free_all: 

    free_bmp_img(&img);
    if (in_bmp != NULL) 
      fclose(in_bmp);
    if (out_bmp != NULL) 
      fclose(out_bmp);
    if (key_file != NULL) 
      fclose(key_file);
    if (msg_file != NULL)
      fclose(msg_file);
  }

  if (strcmp(argv[1], "extract") == 0) {
    if (argc != 5) {
      printf("Invalid numbfer of arguments\n");
      return 0;
    }

    FILE  *in_bmp, 
          *key_file,
          *msg_file;
    bmp_img_t img;

    in_bmp = fopen(argv[2], "rb");
    if (in_bmp == NULL) 
      goto free_all_extract;

    if (load_bmp(in_bmp, &img) == -1) {
      printf("Failed to load img");
      goto free_all_extract;
    }

    key_file = fopen(argv[3], "r");
    if (key_file == NULL) {
      printf("Failed to open key file\n");
      goto free_all_extract;
    }
    
    msg_file = fopen(argv[4], "w");
    if (msg_file == NULL) {
      printf("Failed to open message file\n");
      goto free_all_extract;
    }

    if (extract(key_file, &img, msg_file) == -1) {
      printf("Failed to extract message\n");
      goto free_all_extract;
    };
    
    free_all_extract: 
    
    if (in_bmp != NULL) 
      fclose(in_bmp);
    if (key_file != NULL)
      fclose(key_file);
    if (msg_file != NULL)
      fclose(msg_file);
    free_bmp_img(&img);
  }
  return 0;
}