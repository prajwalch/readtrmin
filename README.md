# ReadTrmIn (Read Terminal Input)
**safe and simple terminal input reader**

## Requirements
* make
* clang/gcc (v9.0.0 or above)

## How To Build And Install

The build is Makefile based. After cloning the repository, run the following commands.

```bash
# go into the cloned directory
$ cd readtrmin

# now run make, it will make shared library and install it to $LD_LIBRARY_PATH
$ make
```

## How to link on your project
Before linking it to your program make sure you build and install it first.
Now first thing you need to do is copy the `readtrmin.h` header file to your project directory because for now while installing the library it doesn't install/copy the header file to include directory itself.  Ok, now let's see by example

```c
//main.c

#include <stdio.h>
#include "input_reader.h"

int main(void)
{
   char single_char = 0;
   readtrmin(&single_char, DEFAULT_LEN, SINGLE_CHAR);
   printf("%c\n", single_char);
}
```
now let's compile it with linking it to library
```bash
$ clang -lreadtrmin main.c
$ ./a.out
```

## API
Readtrmin provided one main function
```c
void readtrmin(void *pointer_arg, int max_input_len, ReadingMode mode);
```
ReadingMode tells the reader what type of data and how much data (follows the max input len if user provide it properly. More details are below) to be read. It also handle the buffer overflow problem. There are total 6 modes defined on the header as enums.

* `SINGLE_CHAR`
    - read only one alphabet character
* `SINGLE_WORD`
    - read only alphabet characters upto _max_input_len_
    - spaces are not allowed
* `SINGLE_ALPHANUMERIC_WORD`
    - read both numbers (as a string not actual number), alphabet or mix but not non-alphabet characters upto _max_input_len_
    - spaces are also allowed
* `WORD_SENTENCE`
    - read whole sentence including space upto _max_input_len_
    - numbers and symbols are not allowed
* `SINGLE_INT`
    - read only one numerical value
* `GROUP_INT`
    - read multiple numbers (it is same as SINGLE_WORD but as a numbers)

and 3 macro function for different 4 level of logging message for only string type.

```c
DEBUG_LOG(m);
DEBUG_INFO(m);
DEBUG_WARN(m);
DEBUG_ERROR(m);
```

## Usage
```c
#include "readtrmin.h"
// you need to include stdio also because macro functions will need printf function
#include <stdio.h> 

int main(void)
{
  // SINGLE_CHAR
  char single_char = 0;
  readtrmin (&single_char, DEFAULT_LEN, SINGLE_CHAR);
  printf("%c\n", single_char);
  
  // SINGLE_WORD
  char single_word[5] = {0};
  readtermin(single_word, 4, SINGLE_WORD);
  DEBUG_LOG(single_word);
  
  // SINGLE_ALPHANUMERIC_WORD
  char single_alpnum[5] = {0};
  readtermin(single_alpnum, 4, SINGLE_ALPHANUMERIC_WORD);
  DEBUG_LOG(single_alpnum);
  
  // WORD_SENTENCE
  char word_sentence[10] = {0};
  readtermin(word_sentence, 9, WORD_SENTENCE);
  DEBUG_LOG(word_sentence);
  
  // SINGLE_WORD
  int single_int = 0;
  readtermin (&single_int, DEFAULT_LEN, SINGLE_INT);
  printf("%d\n", single_int);
  
  // GROUP_INT
  int group_int = 0;
  readtermin (&group_int, 5, GROUP_INT);
  printf("%d\n", group_int);
}
```

## License

MIT

---

> GitHub [@PrajwalCH](https://github.com/PrajwalCH) &nbsp;&middot;&nbsp;
> Twitter [@prjwlCH](https://twitter.com/prjwlCH)

