#include "string_utils.h"

// @see https://stackoverflow.com/a/45582189/3618650
char* trim(const char *str, size_t n)
{
    // do nothing
    if(n == 0) return 0;

    char *reduced = str;

    // ptr stop at the first non-leading space char
    while(isspace(*str)) str++;

    if(*str == '\0') {
        reduced[0] = '\0';
        return 0;
    }

    size_t i = 0;

    // copy char to reduced until '\0' or i == n - 1
    for(i = 0; i < n - 1 && *str != '\0'; i++){
        reduced[i] = *str++;
    }

    // deal with the trailing space
    while(isspace(reduced[--i]));

    reduced[++i] = '\0';

    return reduced;
}
