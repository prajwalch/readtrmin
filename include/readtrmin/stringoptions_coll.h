#ifndef READTRMIN_STRINGOPTIONS_COLL_H

#include "stringoptions_type.h"

const StringOptions default_stringoption = {
  .allow_space = false,
  .allow_number = false,
  .allow_symbol = false,
  .allow_uppercase = true,
  .allow_lowercase = true
};

#endif // READTRMIN_STRINGOPTIONS_COLL_H
