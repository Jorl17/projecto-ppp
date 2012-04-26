#include "datatypes.h"
#include <stdlib.h> /* For NULL, size_t */

Team*      Teams;        /* All teams, ordered alphabetically */
size_t     NumTeams;     /* We don't have a const keyword...  */
GameList*  Games;        /* Has all games ordered by date */
GameList*  LastGameList; /* Points to the last listed game list. */

/* Stupid C90 disallows "dot" initialization. */
Game nullGame = { /*.outcome=*/     0,
                  /*.date=*/        {0,0,0},
                  /*.homeTeam=*/    NULL,
                  /*.awayTeam=*/    NULL};
