#ifndef READTRMIN_STRINGOPTIONS_H

#define READTRMIN_STRINGOPTIONS_H

#include <stdbool.h>

typedef struct StringOptions {
    bool allow_space;
    bool allow_number;
    bool allow_symbol;
    bool allow_uppercase;
    bool allow_lowercase;
} StringOptions;

StringOptions readtrmin_stropts_default = {
    .allow_space = true,
    .allow_number = true,
    .allow_symbol = true,
    .allow_uppercase = true,
    .allow_lowercase = true
};

StringOptions readtrmin_stropts_alphanum = {
    .allow_space = false,
    .allow_number = true,
    .allow_symbol = false,
    .allow_uppercase = true,
    .allow_lowercase = true
};

#endif /* READTRMIN_STRINGOPTIONS_H */

