#include <stdio.h>
#include "str.h"
#include <string.h>

void print_str(char * str) {
  for (; *str; str++) {
    printf("%c", *str);
  }
}

int main() {
  char other_str[] = "тест";
  
  printf("%zu", strlen(other_str));

  return 0;
}