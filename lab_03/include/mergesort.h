#pragma once
#include <stdlib.h>

int my_mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*));