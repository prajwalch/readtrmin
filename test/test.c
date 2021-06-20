#include <stdio.h>
#include "input_reader.h"

int main(void)
{
  DEBUG_LOG("single char");
  char single_char = 0;
  read_console_input(&single_char, DEFAULT_LEN, SINGLE_CHAR);
  printf("%c\n", single_char);
}
