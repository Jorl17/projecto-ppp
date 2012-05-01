#include <stdio.h> /* printf(), fflush() */
#include "Date.h"

/**
  Compare 2 dates. Returns:
   0  if d1 == d2
  -1  if d1 <  d2
   1  if d1 >  d2
**/
int compareDates(Date d1, Date d2) {
    if (   d1.year==d2.year   &&
           d1.month==d2.month &&
           d1.day == d2.day
       )
        return 0;

    if ( d2.year > d1.year)
        return -1;
    else if (d2.year < d1.year)
        return 1;
    else if (d2.month > d1.month)
        return -1;
    else if (d2.month < d1.month)
        return 1;
    else if (d2.day > d1.day)
        return -1;
    else /* Hence (d2.day < d1.day) */
        return 1;
}

void printDate(Date d, bool longFormat) {
    if (longFormat)
        return ; /* FIXME: Do long format printing here... */
    else
        printf("%2d/%2d/%4d", d.day, d.month, d.year);fflush(stdout);
}

Date DATEMAX = {(uint8_t)-1, (uint8_t)-1, (unsigned int)-1};
Date DATEMIN = {0,0,0};
