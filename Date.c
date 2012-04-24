#include "Date.h"

/**
  Compare 2 dates. Returns:
   0  if d1 == d2
  -1  if d1 <  d2
   1  if d1 >  d2
**/
int compareDates(const Date d1, const Date d2) {
    if (   d1.year==d2.year   &&
           d1.month==d1.month &&
           d1.day == d2.month
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
