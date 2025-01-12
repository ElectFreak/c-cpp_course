#ifndef H_STR
#define H_STR

#include <stdlib.h>

char * my_strcpy(char * restrict s1, const char * restrict s2);
char * my_strcat(char * restrict s1, const char * restrict s2);
int my_strcmp(const char * s1, const char * s2); 
size_t my_strlen(const char * s);
size_t wrong_my_strlen(const char * s);

#endif