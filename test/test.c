#include <stdio.h>
#include "readtrmin.h"

extern StringOptions default_string_option;

int main(void)
{
  printf("____char\n");
  char single_char = 0;
  readtrmin_char(&single_char);
  printf("%c\n", single_char);

  printf("____string\n");
  StringOptions user_option = {
    .allow_space = true,
    .allow_number = false,
    .allow_symbol = true,
    .allow_uppercase = false,
    .allow_lowercase = true
  };
  char string[5];
  readtrmin_string(string, 5, 3, &user_option);
  printf("%s\n", string);
  
  printf("____int\n");
  long lg_int = 0;
  readtrmin_int(&lg_int, 9);
  printf("%li\n", lg_int);
}
