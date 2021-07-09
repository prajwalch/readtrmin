#include "str_util.h"

#include <ctype.h>
#include <string.h>

void 
print_error(const char *message)
{
  TRM_ERROR(message);
  return;
}

void 
clear_buffer(char *buffer, size_t buffer_size)
{
  memset(buffer, 0, buffer_size);
}

static int 
is_symbol(int ch)
{
  if (!isalpha(ch) && !isdigit(ch))
    return 1;
  return 0;
}

void
parse_string(const char *buffer, 
             size_t buffer_length, 
             struct TakenString *taken_string)
{
  int ch = 0;
  for (size_t index = 0; index < buffer_length; 
       index += 1) {
    ch = buffer[index];
    
    if (isspace(ch)) {
      // don't re-assign the found indicator i.e true
      // if indicator was already set when sub-string was found on previous iteration
      if (!taken_string->has_whitespace)
        taken_string->has_whitespace = true;
    }
    
    if (isdigit(ch)) {
      if (!taken_string->has_number)
        taken_string->has_number = true;
    }
    
    if (is_symbol(ch)) {
      if (!taken_string->has_symbol)
        taken_string->has_symbol = true;
    }
    
    if (isupper(ch)) {
      if (!taken_string->has_uppercase)
        taken_string->has_uppercase = true;
    }
    
    if (islower(ch)) {
      if (!taken_string->has_lowercase)
        taken_string->has_lowercase = true;
    }
  }
}

struct TakenString
init_TakenString_struct()
{
  struct TakenString default_value = {
    .has_whitespace = false,
    .has_number = false,
    .has_symbol = false,
    .has_uppercase = false,
    .has_lowercase = false
  };
  return default_value;
}

bool 
is_null_input(const char *buffer)
{
  if (buffer[0] == '\0')
    return true;
  return false;
}

void 
flush_input_buffer()
{
  int c = 0;
  while ((c = getchar()) != '\n' && c != EOF);
}

void
set_null_terminator(char *buffer, size_t index)
{
  buffer[index] = '\0';
}

static size_t 
find_LF_index(const char *buffer, size_t buffer_size)
{
  for (size_t index = 0; 
       index < buffer_size; index++) {
    if (buffer[index] == '\n')
      return index;
  }
  // \n not found
  return buffer_size + 1;
}

size_t 
replace_LF_with_NUL(char *buffer, 
                    size_t buffer_size, 
                    size_t expected_LF_index)
{
  size_t found_LF_index = find_LF_index(buffer,buffer_size);
 
  // find_LF_index will return buffer_size + 1 if line feed isn't on the buffer 
  if (found_LF_index > buffer_size) {
    // remove all buffer left in the stdin
    flush_input_buffer();
    
    if (buffer[expected_LF_index] != '\0')
      set_null_terminator(buffer, expected_LF_index);
    
    return expected_LF_index;
  }

  if (found_LF_index > expected_LF_index) {
    set_null_terminator(buffer, expected_LF_index);
    return expected_LF_index;
  }

  set_null_terminator(buffer, found_LF_index);
  return found_LF_index;
}

bool 
has_buffer_overflow(const char *buffer, 
                    size_t buffer_size)
{
  char last_byte = buffer[buffer_size - 1];
  if (last_byte != 0 && last_byte != '\n')
    return true;
  return false;
}

bool 
get_input(char *buffer, size_t buffer_size)
{
  if (fgets(buffer, buffer_size, stdin) == NULL) {
    print_error("expected some input but found nothing");
    return false;
  }
  return true;
}
