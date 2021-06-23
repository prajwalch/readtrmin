#include "readtrmin.h"
#include <stdio.h>

int main(void)
{
  DEBUG_LOG("single char");
  char single_char = 0;
  read_console_input(&single_char, 0, SINGLE_CHAR);
  printf("%c\n", single_char);

  DEBUG_LOG("single word");
  char single_word[5];
  read_console_input(single_word, 5, SINGLE_WORD);
  DEBUG_LOG(single_word);
}
