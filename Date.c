#include <stdio.h> /* printf(), fflush() */
#include <string.h> /* strtok() */
#include "Date.h"
#include "string_functions.h" /* readString() */

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

Date getDateFromUser(const char* msg) {
#define MAX_DATE_SIZE 12 /* dd/mm/aaaa 0 -- the extra space has an explanation below.*/
#define MIN_DATE_CHARACTERS 7/* d/m/aa\0 */
    size_t read;
    char str[MAX_DATE_SIZE];
    char* token;
    Date ret;
    if (msg) {
        printf("%s: ", msg); fflush(stdout);
    }

    read = readString(str, MAX_DATE_SIZE-1);
    /* Add a space at the end because of strtok() eating it up as if it were a token */
    str[read]=' ';
    str[read+1]='\0';

    if (read < MIN_DATE_CHARACTERS)
        goto err;

    token = strtok(str, "/");
    if (!token)
        goto err;
    ret.day = (uint8_t)atoi(token);

    token = strtok(NULL, "/");
    if (!token)
        goto err;
    ret.month = (uint8_t)atoi(token);

    token = strtok(NULL, "/");
    if (!token)
        goto err;
    ret.year = (unsigned int)atoi(token);

    if (ret.year <= 99)
        ret.year += 2000; /* FIXME: assume yy means 20yy or 19yy? */

    if (isValidDate(ret))
        return ret;

    err:
    return DATEMIN;
}

/*
   Returns true if y is a leap year. 0 otherwise.
   As per http://en.wikipedia.org/wiki/Leap_year#Algorithm.
*/
static bool isLeapYear(unsigned int y) {
    if (y%4 == 0) {
        if (y%200 == 0) {
            if (y%400 == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

bool isValidDate(Date d) {
    uint8_t month_days[12] = {31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};

    if(d.month > 12 || d.month==0)
        return false;

    if (isLeapYear(d.year))
        month_days[1] = 29;

    if (d.day>0 && d.day <= month_days[d.month-1])
        return true;

    return false;
}
