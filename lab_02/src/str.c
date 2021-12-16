#include <stdlib.h>
#include "str.h" 

char * my_strcpy(char * restrict s1, const char * restrict s2) { // copy s2 to s1
  char * original_s1 = s1;

  while (*s1++ = *s2++);

  return original_s1;
} 

char * my_strcat(char * restrict s1, const char * restrict s2) { // copy s2 to the end of s1
  char * original_s1 = s1;

  if (*s1) while (*++s1);

  while (*s1++ = *s2++);

  return original_s1;
}

int my_strcmp(const char * s1, const char * s2) { // compare s1 and s2
  while (*s1 && *s2) {
    if (*s1 > *s2) {
      return 1;
    } else if (*s1 < *s2) {
      return -1;
    }

    s1++, s2++;
  }

  if (*s1) return 1;
  if (*s2) return -1;

  return 0;
}

size_t my_strlen(const char * s) { // get length of s
  size_t counter = 0;

  if (*s) while(counter++, *++s);

  return counter;
}