#ifndef TRMIN_STR_UTIl_H
#define TRMIN_STR_UTIl_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define TRM_ERROR(m) \
  fprintf(stderr, "error: %s\n", m);

void 
print_error(const char *message);

bool 
has_lowercase(const char *buffer, size_t buffer_length);

bool 
has_uppercase(const char *buffer, size_t buffer_length);

bool 
has_symbol(const char *buffer, size_t buffer_length);

bool 
has_number(const char *buffer, size_t buffer_length);

bool 
has_whitespace(const char *buffer, size_t buffer_length);

bool 
is_null_input(const char *buffer);

void 
flush_input_buffer();

size_t 
find_LF_position(const char *buffer, size_t buffer_length);

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