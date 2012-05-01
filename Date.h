#ifndef DATE_H
#define DATE_H 1
#include "fixsizedtypes.h" /* uint8_t, bool */

typedef struct _Date {
    uint8_t day, month;
    unsigned int year;
} Date;

int compareDates(Date d1, Date d2);
void printDate(Date d, bool longFormat);
extern Date DATEMAX, DATEMIN;

#endif /* DATE_H */
