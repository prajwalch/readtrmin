#ifndef READTRMIN_H
#define READTRMIN_H

#include <stdbool.h>
#include <stddef.h>

#include "stringoptions.h"

bool
readtrmin_char(char *pointer_arg);

bool
readtrmin_string(char *buffer_arg,
                 size_t buffer_size,
                 size_t max_input_len,
                 StringOptions *string_option);

bool
readtrmin_int(long *pointer_arg,
              size_t  max_input_len);

/*bool
  readtrmin_float(double *pointer_arg,
  size_t const  max_input_len);
  */
#endif
