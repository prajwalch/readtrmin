#include "str_util.h"

#include <stdio.h>
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

typedef int (*CallBackFunc_t)(int);

static bool 
search_char(const char *buffer, 
            size_t buffer_length, 
            CallBackFunc_t callback)
{
  for (size_t index = 0; 
       index < buffer_length; index += 1) {
    if (callback(buffer[index]))
      return true;
  }

  return false;
}

bool 
has_lowercase(const char *buffer, size_t buffer_length)
{
  return search_char(buffer, buffer_length, &islower);
}

bool 
has_uppercase(const char *buffer, size_t buffer_length)
{
  return search_char(buffer, buffer_length, &isupper);
}

static int 
is_symbol(int ch)
{
  if (!isalpha(ch) && !isdigit(ch))
    return 1;
  return 0;
}

bool 
has_symbol(const char *buffer, size_t buffer_length)
{
  return search_char(buffer, buffer_length, &is_symbol);
}

bool 
has_number(const char *buffer, size_t buffer_length)
{
  return search_char(buffer, buffer_length, &isdigit);
}

bool 
has_whitespace(const char *buffer, size_t buffer_length)
{ 
  return search_char(buffer, buffer_length, &isspace);
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
  while ((c = getchar()) != '\n' && (c != EOF));
}

void
set_null_terminator(char *buffer, size_t index)
{
  buffer[index] = '\0';
}

size_t 
find_LF_position(const char *buffer, 
                 size_t buffer_size)
{
  for (size_t index = 0; 
       index < buffer_size; index++) {
    if (buffer[index] == '\n')
      return index;
  }
  // if line feed is not found on any index it will return length + 1 
  return buffer_size + 1;
}

size_t 
replace_LF_with_NUL(char *buffer, 
                    size_t buffer_size, 
                    size_t expected_LF_index)
{
  //size_t found_LF_index = find_LF_position(buffer, buffer_size);
  
  size_t found_LF_index = strcspn(buffer,"\n");
 
  // if \n is not found that means it is left in stdin buffer
  if (found_LF_index == (buffer_size - 1)) {
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
