#include "mergesort.h"
#include <stdlib.h>
#include <assert.h>

void cpy(char* from, char* to, size_t size) {
  for (size_t i = 0; i < size; i++) 
    *(char*)to++ = *(char*)from++;
}

void my_mergesort_help(char* arr, char* buffer, size_t left, size_t right, size_t elements, size_t element_size, int (*comparator)(const void *, const void*));

int my_mergesort(void* array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
  void* buffer = malloc(elements * element_size);
  if (buffer == NULL) {
    return -1;
  }
  my_mergesort_help((char*)array, (char*)buffer, 0, elements - 1, elements, element_size, comparator);  
  free(buffer);
  return 0;
}

void my_mergesort_help(char* arr, char* buffer, size_t left, size_t right, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
  if (left == right) {
    return;
  }

  size_t middle = (left + right) / 2;

  my_mergesort_help(arr, buffer, left, middle, elements, element_size, comparator);
  my_mergesort_help(arr, buffer, middle + 1, right, elements, element_size, comparator);

  size_t l_counter = left;
  size_t r_counter = middle + 1;
  size_t buf_counter = 0;

  while (l_counter <= middle || r_counter <= right) {
    if (l_counter > middle) {
      cpy(arr + r_counter * element_size, buffer + buf_counter * element_size, element_size);
      r_counter++;
    } else if (r_counter > right) {
      cpy(arr + l_counter * element_size, buffer + buf_counter * element_size, element_size);
      l_counter++;
    } else if (comparator((void*)(arr + l_counter * element_size), (void*)(arr + r_counter * element_size)) < 0) {
      cpy(arr + l_counter * element_size, buffer + buf_counter * element_size, element_size);
      l_counter++;
    } else {
      cpy(arr + r_counter * element_size, buffer + buf_counter * element_size, element_size);
      r_counter++;
    }

    buf_counter++;
  }
  
  for (size_t i = 0; i < right - left + 1; i++) {
    cpy(buffer + i * element_size, arr + (left + i) * element_size, element_size);
  }
}