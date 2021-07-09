#ifndef READTRMIN_STR_UTIl_H
#define READTRMIN_STR_UTIl_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define TRM_ERROR(m) \
  fprintf(stderr, "error: %s\n", m);

struct TakenString {
  bool has_whitespace;
  bool has_number;
  bool has_symbol;
  bool has_uppercase;
  bool has_lowercase;
};

void 
print_error(const char *message);

void 
clear_buffer(char *buffer, size_t buffer_size);

void
parse_string(const char *buffer, 
             size_t buffer_length, 
             struct TakenString *taken_string);

struct TakenString
init_TakenString_struct();

bool 
is_null_input(const char *buffer);

void 
flush_input_buffer();

void 
set_null_terminator(char *buffer, size_t index);

size_t 
replace_LF_with_NUL(char *buffer,
                    size_t buffer_length,
                    size_t expected_LF_index);

bool 
has_buffer_overflow(const char *buffer, 
                    size_t buffer_length);

bool 
get_input(char *buffer, size_t buffer_size);
#endif
