#pragma once

#define DEFAULT_LEN 1

#define DEBUG_LOG(m) \
  printf("%s\n", m);
#define DEBUG_INFO(m) \
  printf("\033[1;32minfo: \033[0m\033[1;37m%s\033[0m\n", m);
#define DEBUG_WARNING(m) \
  printf("\033[1;33mwarning: \033[0m\033[1;37m%s\033[0m\n", m);
#define DEBUG_ERROR(m) \
  fprintf(stderr, "\033[1;31merror: \033[0m\033[1;37m%s\033[0m\n", m);

enum ReaderModes {
  SINGLE_CHAR,
  SINGLE_WORD,
  SINGLE_ALPHANUMERIC_WORD,
  WORD_SENTENCE,
  SINGLE_INT,
  GROUP_INT,
};
typedef enum ReaderModes ReadingMode;

void read_console_input(void *pointer_arg, 
    size_t max_input_len, 
    ReadingMode mode);
