#pragma once

#define DEBUG_LOG(m) \
  printf("[log]: %s\n", m);
#define DEBUG_INFO(m) \
  printf("\033[1;32m[info]: %s\033[0m\n", m);
#define DEBUG_WARNING(m) \
  printf("\033[1;33m[warning]: %s\033[0m\n", m);
#define DEBUG_ERROR(m) \
  fprintf(stderr, "\033[1;31m[error]: %s\033[0m\n", m);

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
    size_t max_buffer_len, 
    ReadingMode mode);
