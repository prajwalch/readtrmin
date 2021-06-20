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
  ReaderMode mode = find_mode("%");
  if (mode == INVALID_MODE)
    fprintf(stderr, "invalid mode\n");
  return 0;

}


