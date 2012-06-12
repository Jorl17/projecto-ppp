#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "string.h"

static int flushInputBuffer(void) {
    char ch;
    int n=0;

    while ((ch = getchar()) != '\n' && ch != EOF) n++;

    return n;
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
