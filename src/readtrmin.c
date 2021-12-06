#include "readtrmin.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "str_util.h"

#define CHAR_MAX_BUF_SIZE 2
#define INT_MAX_BUF_SIZE 10

#define ADJUST_INPUT_LEN(input_len, buf_size) \
    do { \
        if (input_len > buf_size) { \
            input_len = buf_size; \
        } else if ((input_len + 1) <= buf_size) { \
            input_len += 1; \
        } \
    } while (0)

bool
readtrmin_int(long *pointer_arg, size_t max_input_len)
{
    assert(pointer_arg != NULL);
    assert(max_input_len < INT_MAX_BUF_SIZE);

    ADJUST_INPUT_LEN(max_input_len, INT_MAX_BUF_SIZE);

    char buffer[INT_MAX_BUF_SIZE] = {0};
    char *error_msg = NULL;

    if (!get_input(buffer, max_input_len))
        return false;

    max_input_len -= 1;
    replace_LF_with_NUL(buffer, max_input_len, max_input_len);

    if (is_null_input(buffer)) {
        error_msg = "expected some input but found nothing";
        goto RETURN_FAILURE;
    }
    errno = 0;
    char *endPtr = NULL;
    long converted_buffer = strtol(buffer, &endPtr, 10);

    if (errno != 0) {
        error_msg = "unable to convert the buffer into number";
        goto RETURN_FAILURE;
    }

    if (strcmp(endPtr, buffer) == 0) {
        error_msg = "unable to find valid data that can be convert into numbers";
        goto RETURN_FAILURE;
    }
    *pointer_arg = converted_buffer;
    return true;

RETURN_FAILURE:
    print_error(error_msg);
    return false;
}

bool
readtrmin_string(char *buffer_arg,
                 size_t buffer_size,
                 size_t  max_input_len,
                 StringOptions *string_option)
{
    assert(buffer_arg != NULL);
    assert(string_option != NULL);
    
    char *error_msg = NULL;
    clear_buffer(buffer_arg, buffer_size);
    ADJUST_INPUT_LEN(max_input_len, buffer_size);

    if (!get_input(buffer_arg, max_input_len))
        return false;

    max_input_len -= 1; // uncount null terminator
    replace_LF_with_NUL(buffer_arg, max_input_len, max_input_len);

    if (is_null_input(buffer_arg)) {
        error_msg = "expected some input but found nothing";
        goto RETURN_FAILURE;
    }
    struct CharacterSets found_char_set = init_CharacterSets_struct();
    search_character_sets(buffer_arg, strlen(buffer_arg), &found_char_set);

    if (!string_option->allow_space) {
        if (found_char_set.space) {
            error_msg = "spaces are not allowed";
            goto RETURN_FAILURE;
        }
    }

    if (!string_option->allow_number) {
        if (found_char_set.number) {
            error_msg = "numbers are not allowed";
            goto RETURN_FAILURE;
        }
    }

    if (!string_option->allow_symbol) {
        if (found_char_set.symbol) {
            error_msg = "special characters are not allowed";
            goto RETURN_FAILURE;
        }
    }

    if (!string_option->allow_uppercase) {
        if (found_char_set.uppercase) {
            error_msg = "uppercase are not allowed, as it is disabled on option";
            goto RETURN_FAILURE;
        }
    }

    if (!string_option->allow_lowercase) {
        if (found_char_set.lowercase) {
            error_msg = "lowecase are not allowed, as it is disabled on option";
            goto RETURN_FAILURE;
        }
    }
    return true;

RETURN_FAILURE:
    clear_buffer(buffer_arg, buffer_size);
    print_error(error_msg);
    return false;
}

bool
readtrmin_char(char *pointer_arg)
{
    *pointer_arg = 0;
    char *error_msg = NULL;
    char buffer[CHAR_MAX_BUF_SIZE] = {0};

    if(!get_input(buffer, CHAR_MAX_BUF_SIZE)) {
        return false;
    }
    replace_LF_with_NUL(buffer, CHAR_MAX_BUF_SIZE, 1);

    if (is_null_input(buffer)) {
        error_msg = "expected some input but found nothing";
        goto RETURN_FAILURE;
    }

    if (!isalpha(buffer[0])) {
        error_msg = "other then alphabet are not allowed";
        goto RETURN_FAILURE;
    }
    assert(isalpha(buffer[0]));
    assert(buffer[1] == '\0');
    *pointer_arg = buffer[0];
    return true;

RETURN_FAILURE:
    print_error(error_msg);
    return false;
}
