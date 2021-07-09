#include <stdio.h>
#include <readtrmin/readtrmin.h>

int main(void)
{
    printf("____char\n");
    char single_char = 0;
    readtrmin_char(&single_char);
    printf("%c\n", single_char);

    printf("____string\n");
    char string[5];
    readtrmin_string(string, 5, 3, &default_stringoption);
    printf("%s\n", string);

    printf("____int\n");
    long lg_int = 0;
    readtrmin_int(&lg_int, 9);
    printf("%li\n", lg_int);
}
