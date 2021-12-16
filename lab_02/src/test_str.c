#include "test_str.h"
#include "str.h"
#include <assert.h>
#include <string.h>

void test_my_strcpy() {
    char s1[100];
    char s2[] = "abc";
    my_strcpy(s1, s2);
    assert(strcmp(s1, s2) == 0);

    char s3[] = "";
    char s4[] = "";
    my_strcpy(s3, s4);
    assert(*s3 == '\0' && *s4 == '\0');
}

void test_my_strcat() {
    char s1[4] = {};
    char s2[] = "abc";
    my_strcat(s1, s2);
    assert(strcmp(s1 ,s2) == 0);

    char s3[] = "";
    char s4[] = "";
    my_strcat(s3, s4);
    assert(*s3 == 0 && *s4 == 0);
}

void test_my_strcmp() {
    char s1[] = "";
    char s2[] = "";
    assert(my_strcmp(s1, s2) == 0);

    char s3[] = "a";
    assert(my_strcmp(s1, s3) < 0);

    char s5[] = "думай позитивно: стакан всегда наполовину полон, всегда";
    char s6[] = "думай позитивно: стакан всегда наполовину полон, всегда";
    assert(my_strcmp(s5, s6) == strcmp(s5, s6));
}

void test_my_strlen() {
  char s1[] = "";
  assert(my_strlen(s1) == 0);

  char s2[] = "гантеля";
  char s3[] = "студень";
  assert(my_strlen(s2) == strlen(s2) && my_strlen(s3) == strlen(s3));

  char s4[] = "сквозное";
  assert(my_strlen(s4) == strlen(s4));
}

void test_wrong_my_strlen() {
  char s[] = "";
  // assert(wrong_my_strlen(s) == 0);
}