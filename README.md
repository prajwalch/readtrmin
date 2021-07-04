# ReadTrmIn
**aim of safe and simple terminal input reader**

## Requirements
* make
* clang (v9.0.0 or above) or gcc

## Key Features
* String reading options to allow or disallow certain things like:
   - whitespace
   - number
   - special characters (#, $, _ and so on)
   - uppercase and lowercase
* Option to specify numbers of input to read for string and int.
* Buffer overflow handling for string


## How To Build And Install

After cloned the repository, run the below command to build:

```bash
make
```

To build for debugging run:
```bash
make DEBUG=1
```

## How to link on your project
 Don't forget to build and install the library first. Once you are done that make a new project and create new 3 source file by the name of `char_example.c`, `string_example.c` and `int_example.c`. Now you can copy and paste the code into each file respectively or manually type.

```c
// char_example.c

#include <stdio.h>
#include <readtrmin/readtrmin.h>

int main(int argc, char **argv)
{
   char single_char = 0;
   readtrmin_char(&single_char);
   // print it
   printf("%c\n", single_char):
}
```

```c
// string_example.c

#include <stdio.h>
#include <readtrmin/readtrmin.h>

int main(int argc, char **argv)
{
   char your_buffer[5] = {0};
   
   /* 
     * readtrmin_string takes 4 arguments
     * char *buffer
     * size_t buffer_size
     * size_t max_input_length
     * StringOptions *option (it is defined on the header file)
   */
   
   readtrmin_string(your_buffer, 5, 4, &default_string_option);
   // print it
   printf("%s\n", your_buffer);
}
```
For more details on StringOptions see the [API](#api) section below.

```c
// int_example.c

#include <stdio.h>
#include <readtrmin/readtrmin.h>
>
int main(int argc, char **argv)
{
   long your_int = 0;
   
   // second argument is max_input_length you want to read.
   // Note that for now more than 9 are not allowed
   readtrmin_int(&your_int, 1);
   // print it
   printf("%lu\n", your_int):
}
```
Now compile one of the examples by linking it with the library as shown below:
```bash
$ clang -lreadtrmin program_name.c
$ ./a.out
```
## API
Readtrmin provided only 3 API functions for now as shown in the above example.

```c
bool readtermin_char(char *pointer_arg);
```
It is straight forward you pass the address of the char type variable and it will take the input and stored it there. It only allows the alphabet letter (aA to zZ).

Return true if the read is successful otherwise false.

```c
bool readtrmin_string(char *buffer_arg, size_t buffer_size, size_t max_input_len, StringOptions *string_option);
```
This function is a bit like the above function but with more features that allow you to give the maximum length of input/string to read as well as what are the things to allowed like ***space, number, special characters, and so on.***  on the string while reading it by passing the options to the function. The type `StringOptions` is defined on the header file `readtrmin.h` as below.

```c
typedef struct StringOptions {
  bool allow_space;
  bool allow_number;
  bool allow_symbol;
  bool allow_uppercase;
  bool allow_lowercase;
} StringOptions;
```
If you didn't want to make your custom options you can use default options which are defined on the header file `stringoptions_coll.h` file as below. This header file can also be include separately by yourself, but by default it is included on the `readtrmin.h` header file. So no need to worry about it.

```c
const StringOptions default_string_option = {
  .allow_space = false,
  .allow_numer = false,
  .allow_symbol = false,
  .allow_uppercase = true,
  .allow_lowercase = true
};
```
For using it you can directly pass the address. See the above string example (string_example.c) shown on the section [How to link on your project](#how-to-link-on-your-project)

Now to create your own option declare it with type `StringOptions` and give value (true or false) to members as shown on below:
```c
StringOptions your_option;
your_option.allow_space = true;
your_option.allow_number = true;
// And so on

// you can also do like this
StringOptions your_options = {
  .allow_space = true,
  .allow_number = true,
  // and so on
}
```

Here is the complete example of using  custom option:
```c
#include <stdio.h>
#include <readtrmin/readtrmin.h>

int main(int argc, char **argc)
{
  StringOptions my_option = {
    .allow_space = false,
    .allow_number = true,
    .allow_symbol = true,
    .allow_uppercase = true,
    .allow_lowercase = true
  };
  
  char username[9] = { 0 };
  readtrmin_string(username, 9, 8, &my_option);
  printf("username: %s\n", username);
}
```

And last we have int reader
```c
bool readtrmin_int(long *pointer_arg, size_t max_input_len);
```
It is also the same as reading char but it only parses number input. you can provide how many numbers you want to take from the input by passing on argument max_input_len. 

***Note that for now it's not allowed to take more than 9 numbers***
## License

MIT

---

> GitHub [@PrajwalCH](https://github.com/PrajwalCH) &nbsp;&middot;&nbsp;
> Twitter [@prjwlCH](https://twitter.com/prjwlCH)

