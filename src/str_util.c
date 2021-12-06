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
search_character_sets(const char *buffer,
                      size_t buffer_length,
                      struct CharacterSets *character_set)
{
    for (size_t i = 0; i < buffer_length; ++i) {
        int ch = buffer[i];

        if (isspace(ch)) {
            // don't re-assign the found indicator i.e true
            // if indicator was already set when sub-string was found on previous iteration
            if (character_set->space == false)
                character_set->space = true;
        }

        if (isdigit(ch)) {
            if (character_set->number == false)
                character_set->number = true;
        }

        if (is_symbol(ch)) {
            if (character_set->symbol == false)
                character_set->symbol = true;
        }

        if (isupper(ch)) {
            if (character_set->uppercase == false)
                character_set->uppercase = true;
        }

        if (islower(ch)) {
            if (character_set->lowercase == false)
                character_set->lowercase = true;
        }
    }
}

struct CharacterSets
init_CharacterSets_struct()
{
    struct CharacterSets default_value = {
        .space = false,
        .number = false,
        .symbol = false,
        .uppercase = false,
        .lowercase = false
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

// return index if LF is found otherwise return buffer_size + 1
static size_t
search_LF_index(const char *buffer, size_t buffer_size)
{
    for (size_t index = 0; index < buffer_size; ++index) {
        if (buffer[index] == '\n')
            return index;
    }
    return buffer_size + 1;
}

size_t
replace_LF_with_NUL(char *buffer, size_t buffer_size, size_t expected_LF_index)
{
    size_t found_LF_index = search_LF_index(buffer, buffer_size);

    // search_LF_index will return buffer_size + 1 if LF not found on the buffer
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
get_input(char *buffer, size_t buffer_size)
{
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        print_error("expected some input but found nothing");
        return false;
    }
    return true;
}
