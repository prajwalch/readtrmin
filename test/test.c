#include <stdio.h>
#include "readtrmin_new.h"

extern StringOptions default_string_option;

int main(void)
{
  char single_char = 'a';
  printf("char add: %p\n", &single_char);
  readtrmin_char(&single_char);
  printf("%c", single_char);

  //char string[5];
  //readtrmin_string(string, 5, 4, &default_string_option);
  //printf("%s\n", string);
}
