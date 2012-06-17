#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "string.h"

int flushBuffer(FILE* f) {
    char ch;
    int n=0;

    while ((ch = fgetc(f)) != '\n' && ch != EOF) n++;

    return n;
}

int flushInputBuffer(void) {
    return flushBuffer(stdin);
}

size_t readStringFile(char* str, size_t maxlen, FILE* f) {
    size_t len;
    if ( ! fgets(str, maxlen, f) )
        return 0;

    len = strlen(str);

    if (str[len-1]=='\n'){
        str[len-1]='\0';
        len--;
    }

    return len;
}

/*
 Reads a string from standard input. Returns the length of the string or 0
 if there was an error.
 */
size_t readString(char* str, size_t maxlen) {
    size_t len;
    if ( ! fgets(str, maxlen, stdin) )
        return 0;

    len = strlen(str);

    if (str[len-1]=='\n'){
        str[len-1]='\0';
        len--;
        /* Clean buffer */
    }
    if (len == maxlen-1) {
        flushInputBuffer();
    }
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

bool strCaseEqual(char* s1, char* s2, size_t n) {
    while (n--) {
        if (!*s1 || !*s2)
            return false;

        if (toupper(*s1) != toupper(*s2))
            return false;
        s1++; s2++;
    }

    return true;
}

void trimString(char* s) {
    char* ptr=s;
    while (*(ptr++) == ' ') ;
    ptr--;
    while(*ptr)
        *(s++) = *(ptr++);

    while (*(--s) == ' ') ;
    *(++s) = '\0';
}

bool strToResult(char* str, uint8_t* pts1, uint8_t* pts2) {
    char* token;
    token = strtok(str, "-");;

    if (token==NULL || !isStrNumber(token))
        return false;
    *pts1 = atoi(token);
    token = strtok(NULL, "-");

    if (*pts1 > 255)
        return false; /* byte overflow */
    if (token==NULL || !isStrNumber(token))
        return false;
    *pts2 = atoi(token);

    if (*pts2 > 255)
        return false; /* byte overflow */

    return true;
}
