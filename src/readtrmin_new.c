#include "readtrmin_new.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "util/str_util.h"

#define NULL_BYTE 1
#define MIN_BUFFER_SIZE 2
#define INT_MAX_BUFFER_SIZE 10

const StringOptions default_string_option = { 
  .allow_space = false,
  .allow_number = false,
  .allow_symbol = false,
  .allow_uppercase = true,
  .allow_lowercase = true
};

bool 
readtrmin_int(long *pointer_arg, size_t max_input_len)
{
  assert(pointer_arg != NULL);
  assert(max_input_len < INT_MAX_BUFFER_SIZE);

  char buffer[INT_MAX_BUFFER_SIZE];
  clear_buffer(buffer, INT_MAX_BUFFER_SIZE);
  
  size_t buffer_length = 0;
  size_t input_length = max_input_len + NULL_BYTE;
  
  if (input_length > INT_MAX_BUFFER_SIZE)
    input_length = INT_MAX_BUFFER_SIZE - 1; 

  if (!get_input(buffer, input_length))
    return false;

  if (has_buffer_overflow(buffer, INT_MAX_BUFFER_SIZE)) {
    flush_input_buffer();
    set_null_terminator(buffer, input_length - 1);
    buffer_length = input_length - 1;
  } else {
    buffer_length = replace_LF_with_NUL(buffer, input_length, input_length - 1);
  }

  if (is_null_input(buffer)) {
    print_error("expected some input but found nothing");
    return false;
  }

  /*if (has_alphabet(buffer, buffer_length)) {
    print_error("other then integers are not allowed");
    return false;
  }*/

  errno = 0;
  char *endPtr = NULL;
  long converted_buffer = strtol(buffer, &endPtr, 10);

  if (errno != 0) {
    print_error("unable to convert the buffer into number");
    return false;
  }

  if (strcmp(endPtr, buffer) == 0) {
    print_error("unable to find valid data that can be convert into numbers");
    return false;
  }

  *pointer_arg = converted_buffer;
  return true;
}

bool 
readtrmin_string(char *buffer_arg, 
                 size_t buffer_size, 
                 size_t  max_input_len, 
                 StringOptions *string_option)
{ 
  assert(buffer_arg != NULL);
  assert(max_input_len < buffer_size);
  assert(string_option != NULL);

  clear_buffer(buffer_arg, buffer_size);
  size_t buffer_length = 0;
  size_t input_length = max_input_len + NULL_BYTE;

  if (input_length > buffer_size)
    input_length = buffer_size - 1;

  if (!get_input(buffer_arg, input_length))
    return false;

  if (has_buffer_overflow(buffer_arg, buffer_size)) {
    flush_input_buffer();
    set_null_terminator(buffer_arg, input_length - 1);
    buffer_length = input_length - 1;
  }
  else {
    // replace_LF_with_NUL will return num of items it found on buffer based on the index where new line is found
    buffer_length = replace_LF_with_NUL(buffer_arg, input_length, input_length -1);
  }

  if (is_null_input(buffer_arg)) {
    print_error("expected some input but found nothing");
    clear_buffer(buffer_arg, buffer_size);
    return false;
  }

  if (!string_option->allow_space) {
    if (has_whitespace(buffer_arg, buffer_length)) {
      print_error("spaces are not allowed");
      clear_buffer(buffer_arg, buffer_size);
      return false;
    }
  }

  if (!string_option->allow_number) {
    if (has_number(buffer_arg, buffer_length)) {
      print_error("numbers are not allowed");
      clear_buffer(buffer_arg, buffer_size);
      return false;
    }
  }

  if (!string_option->allow_symbol) {
    if (has_symbol(buffer_arg, buffer_length)) {
      print_error("special characters are not allowed");
      clear_buffer(buffer_arg, buffer_size);
      return false;
    }
  }

  if (!string_option->allow_uppercase) {
    if (has_uppercase(buffer_arg, buffer_length)) {
      print_error("uppercase are not allowed, as it is disabled on option");
      clear_buffer(buffer_arg, buffer_size);
      return false;
    } 
  }

  if (!string_option->allow_lowercase) {
    if (has_lowercase(buffer_arg, buffer_length)) {
      print_error("lowecase are not allowed, as it is disabled on option");
      clear_buffer(buffer_arg, buffer_size);
      return false;
    }
  }

  return true;
}

bool 
readtrmin_char(char *pointer_arg)
{
  *pointer_arg = 0;
  char buffer[MIN_BUFFER_SIZE];
  clear_buffer(buffer, MIN_BUFFER_SIZE);

  if(!get_input(buffer, MIN_BUFFER_SIZE)) {
    return false;
  }

  if (has_buffer_overflow(buffer, MIN_BUFFER_SIZE)) {
    flush_input_buffer();
    set_null_terminator(buffer, 1);
  } else {
    replace_LF_with_NUL(buffer, MIN_BUFFER_SIZE, 1);
  }

  if (is_null_input(buffer)) {
    print_error("expected some input but found nothing");
    return false;
  }

  if (!isalpha(buffer[0])) {
    print_error("other then alphabet are not allowed");
    return false;
  }

  assert(isalpha(buffer[0]));
  assert(buffer[1] == '\0');
  *pointer_arg = buffer[0];
  return true;
}
