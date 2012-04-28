#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
  Reads a string from standard input. Returns the length of the string or 0
  if there was an error.
*/
size_t readString(char* str, size_t maxlen) {
    size_t len;
    if ( ! fgets(str, maxlen, stdin) )
        return 0;

    len = strlen(str);
    str[len-1]='\0';
    return len;
}

/*
  Checks if a string is a number.
 */
bool isStrNumber(const char* s) {
    while ( *s ) {
        if (!isdigit(*(s++)))
                return false;
    }

    return true;
}