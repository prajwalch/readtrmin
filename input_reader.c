#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "input_reader.h"

#define DEFAULT_MIN_BYTE_ALLOWED 1
#define DEFAULT_MAX_BYTE_ALLOWED 4
#define DEFAULT_MIN_BUFFER_SIZE 2
#define DEFAULT_MAX_BUFFER_SIZE 5
#define NULL_BYTE 1
#define BUFFER_OVERFLOW_MESSAGE "found buffer overflow"
#define STRING_FOUND_SPACE_MSG "expected only alphabet letters but also found a space/empty on it"
#define STRING_FOUND_NUMBER_MSG "expected only alphabet letters but also found a number on it"
#define STRING_FOUND_SYMBOL_MSG "expected only alphabet letters but also found a symbol on it"
#define INT_FOUND_WHITESPACE_MSG "expected a integer but also found a space on it"
#define INT_FOUND_ALPHABET_MSG "expected only integers but also found a alphabet on it"

static void error_and_exit(const char *message)
{
  //fprintf(stderr, "%s", message);
  DEBUG_ERROR(message);
  exit(EXIT_FAILURE);
}

static void info_and_exit(const char *message)
{
  //fprintf(stderr, "%s", message);
  DEBUG_INFO(message);
  exit(EXIT_FAILURE);
}

static bool is_whitespace(char byte)
{
  printf("is lf: %i\n", byte == '\n');
  if ((isspace(byte) && isblank(byte)) || byte == '\n') {
    return true;
  }

  return false;
}

static bool has_buffer_overflow(char *buffer, 
    size_t buffer_length)
{
  int buff_last_byte = buffer[buffer_length - 1];
  if (buff_last_byte != 0 
      && buff_last_byte != '\n') {
    return true;
  }

  return false;
}

static bool has_whitespace(char *buffer, 
    size_t buffer_length)
{
  for (size_t index = 0; index < buffer_length; index++) {
    if (is_whitespace(buffer[index]))
      return true;
  }

  return false;
}

static bool has_alphabet(char *buffer, size_t buffer_length)
{
  for (size_t index = 0; index < buffer_length; index++) {
    if (isalpha(buffer[index]))
      return true;
  }

  return false;
}

static bool has_number(char *buffer, 
    size_t buffer_length)
{
  // hi --> 3

  for (size_t index = 0; index < buffer_length; index++) {
    if (isdigit(buffer[index]))
      return true;
  }
  return false;
}

static bool has_symbol(char *buffer, 
    size_t buffer_length)
{
  for (size_t index = 0; index < buffer_length; index++) {
    if (!isdigit(buffer[index]) 
        && !is_whitespace(buffer[index]) 
        && !isalpha(buffer[index]))
      return true;
  }

  return false;
}

// -----------check functions-----------

static void check_for_whitespace(char *buffer, size_t buffer_length, char *msg)
{
  if (has_whitespace(buffer, buffer_length))
    error_and_exit(msg);
}

static void check_for_alphabet(char *buffer, size_t buffer_length, char *msg)
{
  if (has_alphabet(buffer, buffer_length))
    error_and_exit(msg);
}

static void check_for_number(char *buffer, size_t buffer_length, char *msg)
{
  if (has_number(buffer, buffer_length))
    error_and_exit(msg);
}

static void check_for_symbol(char *buffer, size_t buffer_length, char *msg)
{
  if (has_symbol(buffer, buffer_length))
    error_and_exit(msg);
}

// ------reader function helpers--------
static void flush_input_buffer()
{
  int ch = 0;
  while (((ch = getchar()) != '\n') && (ch != EOF));
  return;
}

static void set_null_terminator(char *buffer, 
    int at_index)
{
  buffer[at_index] = '\0';
  return;
}

static size_t find_LF_position(char *buffer, 
    size_t buffer_length)
{
  size_t index = 0;
  for (; index < buffer_length; index++) {
    if (buffer[index] == '\n')
      return index;
  }
  return buffer_length - 1;
}

static void get_buffer(char *buffer, size_t buffer_size)
{
  if (fgets(buffer, buffer_size + 1, stdin) == NULL)
    error_and_exit("expected a input but found nothing");
}

static int convert_to_int(char *buffer)
{
  long int converted_int = strtol(buffer, NULL, 10);
  if (converted_int == 0) {
    error_and_exit("couldn't convert the buffer to int");
  }

  return (int)converted_int;
}

static void INT_set_pointer_arg(int *pointer_arg, char *buffer)
{
  int conv_int = convert_to_int(buffer);
  *pointer_arg = conv_int;
  return;
}

static void STRING_set_pointer_arg(char *pointer_arg, char *buffer, size_t buffer_length)
{
  memcpy(pointer_arg, buffer, buffer_length + 1);
  return;
}

static void SB_fix_buff_overflow(char *buffer)
{
  if (has_buffer_overflow(buffer, 2)) {
    flush_input_buffer();
    DEBUG_WARNING(BUFFER_OVERFLOW_MESSAGE);
  }

  set_null_terminator(buffer, 1);
  return;
}

static void SB_write_buffer(char *buffer)
{
  get_buffer(buffer, 2);
  SB_fix_buff_overflow(buffer);
}

static void MB_fix_buff_overflow(char *buffer, 
    size_t *buffer_length, 
    size_t max_byte_allowed)
{
  size_t expected_LF_position = max_byte_allowed;
  if (has_buffer_overflow(buffer, *buffer_length)) {
    flush_input_buffer();
    DEBUG_WARNING(BUFFER_OVERFLOW_MESSAGE);
    set_null_terminator(buffer, expected_LF_position);
    *buffer_length = expected_LF_position;
  } else {
    size_t LF_position = find_LF_position(buffer, *buffer_length);
    assert(LF_position != 0);

    if (LF_position > expected_LF_position)
      LF_position = expected_LF_position;

    set_null_terminator(buffer, LF_position);
    *buffer_length = LF_position;
  }
}

static size_t MB_write_buffer(char *buffer, size_t buffer_size, size_t max_byte_allowed)
{
  get_buffer(buffer, buffer_size);
  size_t buffer_length = buffer_size;
  MB_fix_buff_overflow(buffer, &buffer_length, max_byte_allowed);
  return buffer_length;
}

static void read_multi_byte(void *pointer_arg, 
    char *buffer, 
    size_t buffer_size, 
    size_t max_byte_allowed,
    ReadingMode mode)
{
  size_t buffer_new_len = MB_write_buffer(buffer, buffer_size, max_byte_allowed);

  if (mode == SINGLE_WORD) {
    DEBUG_LOG("detected single word");
    check_for_whitespace(buffer, buffer_new_len, STRING_FOUND_SPACE_MSG);

    check_for_number(buffer, buffer_new_len, STRING_FOUND_NUMBER_MSG);

    check_for_symbol(buffer, buffer_new_len, STRING_FOUND_SYMBOL_MSG);

    STRING_set_pointer_arg((char *)pointer_arg, buffer, buffer_new_len + 1);
    return;
  }
  if (mode == SINGLE_ALPHANUMERIC_WORD) {
    check_for_whitespace(buffer, buffer_new_len, STRING_FOUND_SPACE_MSG);

    check_for_symbol(buffer, buffer_new_len, STRING_FOUND_SYMBOL_MSG);

    STRING_set_pointer_arg((char *)pointer_arg, buffer, buffer_new_len + 1);
    return;
  }

  if (mode == WORD_SENTENCE) {
    check_for_number(buffer, buffer_new_len, STRING_FOUND_NUMBER_MSG);

    STRING_set_pointer_arg((char *)pointer_arg, buffer, buffer_new_len + 1);
    return;
  }

  if (mode == GROUP_INT) {
    check_for_whitespace(buffer, 
        buffer_new_len, INT_FOUND_WHITESPACE_MSG);

    check_for_alphabet(buffer, 
        buffer_new_len, INT_FOUND_ALPHABET_MSG);

    INT_set_pointer_arg((int *)pointer_arg, buffer);
  }
}

static void read_single_byte(void *pointer_arg, char *buffer, ReadingMode mode)
{
  SB_write_buffer(buffer);

  if (mode == SINGLE_CHAR) {
    if (is_whitespace(buffer[0]) || buffer[0] == '\n')
      error_and_exit("expected only a alphabet letter but found space");

    if (isdigit(buffer[0]))
      error_and_exit("expected only a alphabet but found a number");
    STRING_set_pointer_arg(pointer_arg, buffer, 1);
  }

  if (mode == SINGLE_INT) {
    if (is_whitespace(buffer[0]) || buffer[0] == '\n')
      error_and_exit("expected only a number but found space");

    if (isalpha(buffer[0]))
      error_and_exit("expected only a number but found a alphabet letter");

    INT_set_pointer_arg((int *)pointer_arg, buffer);
  }
}

static size_t verify_buffer_size(size_t buffer_size, ReadingMode mode)
{
  if (buffer_size != 2 
      && (mode == SINGLE_CHAR 
        || mode == SINGLE_INT)) {
    return 0;
  }

  if (buffer_size < 1 
      && (mode != SINGLE_CHAR 
        || mode != SINGLE_INT)) {
    return 0;
  }
  return buffer_size;
}

static size_t verify_input_len(size_t input_len, 
    ReadingMode mode)
{
  if (input_len != 1 
      && (mode == SINGLE_CHAR || mode == SINGLE_INT)) {
    return DEFAULT_MIN_BYTE_ALLOWED;
  }

  if ((input_len != 1 || input_len < 1) 
      && (mode != SINGLE_CHAR || mode != SINGLE_INT)) {
    return DEFAULT_MAX_BYTE_ALLOWED;
  }

  return input_len;
 }

void read_console_input(void *pointer_arg, 
    size_t max_input_len, 
    size_t max_buffer_size, 
    ReadingMode mode)
{
  size_t buffer_size = verify_buffer_size(max_buffer_size, mode);
  size_t max_byte_toread = verify_input_len(max_input_len, mode);

  if (buffer_size == 0)
    error_and_exit("buffer size shouldn't be less then 1");

  if (max_byte_toread >= buffer_size)
    max_byte_toread = buffer_size - 1;

  if (max_byte_toread == 0)
    error_and_exit("couldn't perform action on max byte zero");

  printf("max byte: %i\n", max_byte_toread);
  printf("max buff: %i\n", buffer_size);

  // raw input/buffer which we read from the console
  char console_buffer[buffer_size];
  memset(console_buffer, 0, buffer_size);

  switch (mode) {
    case (SINGLE_CHAR):
    case (SINGLE_INT):
      DEBUG_LOG("single byte");
      read_single_byte(pointer_arg, console_buffer, mode);
      break;
    case (SINGLE_WORD):
    case (SINGLE_ALPHANUMERIC_WORD):
    case (WORD_SENTENCE):
    case (GROUP_INT):
      read_multi_byte(pointer_arg, 
          console_buffer, 
          buffer_size, 
          max_byte_toread, 
          mode);
      break;
    default:
      printf("error");
      break;
  }
}
