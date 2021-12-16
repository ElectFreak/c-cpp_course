#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

const char memory_error[] = "Error: memory allocation failed.";

int int_gt_comparator(const void* a, const void* b) {
  if (*(int*)a == *(int*)b) return 0;
  return (*(int*)a < *(int*)b) ? -1 : 1;
}

int char_gt_comparator(const void* a, const void* b) {
  if (*(char*)a == *(char*)b) return 0;
  return (*(char*)a < *(char*)b) ? -1 : 1;
}

int string_gt_comparator(const void* a, const void* b) {
  return strcmp(*(char**)a, *(char**)b);
}

int main(int argc, char** argv) {
  int arr_size = argc - 2;

  if (arr_size < 1) {
    return 0;
  }

  if (strcmp(argv[1], "int") == 0) {
    int* arr = malloc(sizeof(int) * arr_size);
    if (arr == NULL) {
      printf("%s", memory_error);
      return 1;
    }
    
    for (int i = 0; i < arr_size; i++) {
      arr[i] = atoi(argv[i + 2]);
    }
    
    if (my_mergesort(arr, arr_size, sizeof(int), int_gt_comparator) != 0) {
      printf("%s", memory_error);
      return 1;
    }
    
    for (int i = 0; i < arr_size - 1; i++)
      printf("%d ", arr[i]);
    printf("%d\n", arr[arr_size - 1]);
    
    free(arr);
  
    return 0;
  }

  if (strcmp(argv[1], "char") == 0) {
    char* arr = malloc(sizeof(char) * arr_size);
    if (arr == NULL) {
      printf("%s", memory_error);
      return 1;
    }
    
    for (int i = 0; i < arr_size; i++) {
      arr[i] = *argv[i + 2];
    }
    
    if (my_mergesort(arr, arr_size, sizeof(char), char_gt_comparator) != 0) {
      printf("%s", memory_error);
      return 1;
    }
    
    for (int i = 0; i < arr_size - 1; i++)
      printf("%c ", arr[i]);
    printf("%c\n", arr[arr_size - 1]);

    free(arr);

    return 0;
  }

  if (strcmp(argv[1], "str") == 0) {
    char** arr = malloc(sizeof(char*) * arr_size);
    if (arr == NULL) {
      printf("%s", memory_error);
      return 1;
    }

    for (int i = 0; i < arr_size; i++) {
      arr[i] = argv[i + 2];
    }

    if (my_mergesort(arr, arr_size, sizeof(char*), string_gt_comparator) != 0) {
      printf("%s", memory_error);
      return 1;
    }

    for (int i = 0; i < arr_size - 1; i++)
      printf("%s ", arr[i]);
    printf("%s\n", arr[arr_size - 1]);

    free(arr);

    return 0;
  }
}