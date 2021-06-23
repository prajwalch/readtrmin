#include <stdio.h>

enum ReadingModes {
  SIGNED_INT,    /* %d signed decimal int */
  //SIGNED_FLOAT,
  UNSIGNED_INT,  /* %u unsigned decimal int */
  UNSIGNED_CHAR, /* %c unsigned character */
  STRING,     /* %s string */
  INVALID_MODE
};
typedef enum ReadingModes ReaderMode;

ReaderMode 
find_mode(char *format)
{
  /* %[*][width][length]type */
  ReaderMode found_mode = INVALID_MODE;
  
  if (format[0] != '%')
    return found_mode;

  switch (format[1]) {
    case 'i':
    case 'I':
      found_mode = SIGNED_INT;
      break;
    case 'u':
    case 'U':
      found_mode = UNSIGNED_INT;
      break;
    case 'c':
    case 'C':
      found_mode = UNSIGNED_CHAR;
      break;
    case 's':
    case 'S':
      found_mode = STRING;
      break;
    default:
      break;
  }

  return found_mode;
}

int main(void)
{
  //PCXString my_name = new_pcxstring(6);
  ReaderMode mode = find_mode("%");
  if (mode == INVALID_MODE)
    fprintf(stderr, "invalid mode\n");
  return 0;
  char pointer_arg = 0;

  ReaderStatus status = read_console_input(1, mode, &pointer_arg);
}

ReaderStatus read_console_input(int max_input_len, ReaderMode, void *pointer_arg)
{
  /*
   * it verifies the length according to mode
   * 1 (DEFAULT_LEN): for 
  */
  int verified_input_len = verify_input_len(max_input_len);
}


