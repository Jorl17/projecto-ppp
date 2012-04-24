#include "datatypes.h"
#include <stdlib.h> /* For NULL */

Team**     gTeams;        /* All teams, ordered alphabetically */
int        gNumTeams;     /* We don't have a const keyword...  */
GameList*  gGameList;     /* Has all games ordered by date */
GameList*  gLastGameList; /* Points to the last listed game list. */

/* Stupid C90 disallows "dot" initialization. */
Game nullGame = { /*.outcome=*/     0,
                  /*.date=*/        {0,0,0},
                  /*.cachedPoints=*/0,
                  /*.homeTeam=*/    NULL,
                  /*.awayTeam=*/    NULL};
