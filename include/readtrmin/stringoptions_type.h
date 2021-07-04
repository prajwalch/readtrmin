#ifndef READTRMIN_STRINGOPTIONS_TYPE_H
#define READTRMIN_STRINGOPTIONS_TYPE_H

#include <stdbool.h>

typedef struct StringOptions {
  bool allow_space;
  bool allow_number;
  bool allow_symbol;
  bool allow_uppercase;
  bool allow_lowercase;
} StringOptions;

#endif // READTRMIN_STRINGOPTIONS_TYPE_H
