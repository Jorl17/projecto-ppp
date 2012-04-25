#ifndef DATE_H
#define DATE_H 1
#include "fixsizedtypes.h"

typedef struct _Date {
    unsigned int year;
    uint8_t month, day;
} Date;

/**
  Compare 2 dates. Returns:
   0  if d1 == d2
  -1  if d1 <  d2
   1  if d1 >  d2
**/
int compareDates(Date d1, Date d2);
void printDate(Date d, bool longFormat);


#endif /* DATE_H */
