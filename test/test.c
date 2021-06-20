#include <stdio.h>
#include "input_reader.h"

int main(int argc, char **argv)
{
  DEBUG_LOG("single char");
  char single_char = 0;
  read_console_input(&single_char, 1, 2, SINGLE_CHAR);
  printf("%c\n", single_char);
  
  DEBUG_LOG("single word");
  char single_word[6];
  read_console_input(&single_word, 5, sizeof(single_word), SINGLE_WORD);
  DEBUG_LOG(single_word);

  DEBUG_LOG("alphanumeric word");
  char alnum_word[6];
  read_console_input(&alnum_word, 5, sizeof(alnum_word), SINGLE_ALPHANUMERIC_WORD);
  DEBUG_LOG(alnum_word);
  
  DEBUG_LOG("word sentence");
  char word_sent[10];
  read_console_input(&word_sent, 19, sizeof(word_sent), WORD_SENTENCE);
  DEBUG_LOG(word_sent);

  DEBUG_LOG("group int");
  int menu_number = 0;
  read_console_input(&menu_number, 4, 5, GROUP_INT);
  printf("%i\n", menu_number);

  DEBUG_LOG("single int");
  int single_int = 0;
  read_console_input(&single_int, 1, 2, SINGLE_INT);
  printf("%i\n", single_int);
}
