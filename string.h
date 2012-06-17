#include <stdio.h>
#include <stdlib.h>
#include "fixsizedtypes.h"

int flushBuffer(FILE* f);
int flushInputBuffer(void);
size_t readStringFile(char* str, size_t maxlen, FILE* f);
size_t readString(char* str, size_t maxlen);
bool isStrNumber(const char*);
bool strCaseEqualn(char* s1, char* s2, size_t n);
bool strCaseEqual(char* s1, char* s2);
void trimString(char* s);
bool strToResult(char* str, uint8_t* pts1, uint8_t* pts2);
void toLower(char s[]);
