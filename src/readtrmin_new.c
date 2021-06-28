#include "readtrmin_new.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "util/str_util.h"

#define MIN_BUFFER_SIZE 2
#define NULL_BYTE 1

const StringOptions default_string_option = { 
  .allow_space = false,
  .allow_number = false,
  .allow_symbol = false,
  .allow_uppercase = true,
  .allow_lowercase = true
};

bool 
readtrmin_string(char *buffer_arg, 
                 size_t buffer_size, 
                 size_t  max_input_len, 
                 StringOptions *string_option)
{ 
  assert(buffer_arg != NULL);
  assert(max_input_len < buffer_size);

#ifdef NDEBUG
  if (max_input_len > buffer_size)
    max_input_len = buffer_size - 1;
#endif

  assert(string_option != NULL);
  size_t buffer_length = max_input_len + NULL_BYTE;
  memset(buffer_arg, 0, buffer_length);

  if (!get_input(buffer_arg, buffer_size))
    return false;

  if (has_buffer_overflow(buffer_arg, buffer_size)) {
    flush_input_buffer();
    set_null_terminator(buffer_arg, buffer_length - 1);
  }
  else {
    // replace_LF_with_NUL will return num of items it found on buffer based on the index where new line is found
    buffer_length = replace_LF_with_NUL(buffer_arg, buffer_length, buffer_length - 1);
  }

  if (!string_option->allow_space) {
    if (has_whitespace(buffer_arg, buffer_length)) {
      print_error("spaces are not allowed");
      return false;
    }
  }

  if (is_null_input(buffer_arg)) {
    print_error("expected some input but found nothing");
    return false;
  }

  if (!string_option->allow_number) {
    if (has_number(buffer_arg, buffer_length)) {
      print_error("numbers are not allowed");
      return false;
    }
  }

  if (!string_option->allow_symbol) {
    if (has_symbol(buffer_arg, buffer_length)) {
      print_error("special characters are not allowed");
      return false;
    }
  }

  if (!string_option->allow_uppercase) {
    if (has_uppercase(buffer_arg, buffer_length)) {
      print_error("uppercase are not allowed, as iit is disabled on option");
      return false;
    } 
  }

  if (!string_option->allow_lowercase) {
    if (has_lowercase(buffer_arg, buffer_length)) {
      print_error("lowecase are not allowed, as it is disabled on option");
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
  memset(buffer, 0, MIN_BUFFER_SIZE);

  if(!get_input(buffer, MIN_BUFFER_SIZE)) {
    return false;
  }

  if (has_buffer_overflow(buffer, MIN_BUFFER_SIZE)) {
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
