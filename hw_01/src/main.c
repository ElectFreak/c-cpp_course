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

    FILE* in_bmp = fopen(argv[2], "rb");
    if (in_bmp == NULL) {
      printf("Failed to open input file\n");
    
      return 0;
    }

    FILE* out_bmp = fopen(argv[3], "wb");
    if (out_bmp == NULL) {
      printf("Failed to open output file\n");
      fclose(in_bmp);
      
      return 0;
    }

    FILE* key_file = fopen(argv[4], "rb");
    if (key_file == NULL) {
      printf("Failed to open key file\n");
      fclose(in_bmp);
      fclose(out_bmp);
      
      return 0;
    }
        
    bmp_img_t img;
    if (load_bmp(in_bmp, &img) == -1) {
      printf("Failed to load image\n");
      fclose(in_bmp);
      fclose(out_bmp);
      fclose(key_file);
      
      return 0;
    } 

    FILE* msg_file = fopen(argv[5], "rb");
    if (msg_file == NULL) {
      printf("Failed to open message file\n");
      fclose(in_bmp);
      fclose(out_bmp);
      fclose(key_file);
      
      return 0;
    }

    char msg[500];
    fscanf(msg_file, "%s", msg);
    int len = strlen(msg);
    key_t* key = malloc(sizeof(key_t) * len * 5);
    if (get_key(key_file, len * 5, key) == -1) {
      printf("Key is not valid\n");
      fclose(in_bmp);
      fclose(out_bmp);
      fclose(key_file);
      free_bmp_img(&img);
      free(key);
      
      return 0;
    }

    // print_key(key, 5);

    if (insert(key, &img, msg) == -1) {
      printf("Failed to insert key\n");
      fclose(in_bmp);
      fclose(out_bmp);
      fclose(key_file);
      free_bmp_img(&img);
      free(key);

      return 0;
    }

    save_bmp(&img, out_bmp);
    
    /* START TEST */
    char mess[3];
    mess[2] = 0;
    extract(key, &img, mess, 2);
    printf("extracted: %s\n", mess);

    /* END TEST */

    free_bmp_img(&img);
    free(key);
    fclose(in_bmp);
    fclose(out_bmp);
    fclose(key_file);
  }

  
  return 0;
}