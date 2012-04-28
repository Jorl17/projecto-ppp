#include "datatypes.h"
#include "GameList.h"
#include <stdlib.h>

Team*      Teams;        /* All teams, ordered alphabetically */
size_t     NUM_TEAMS;
GameList*  Games;        /* Has all games ordered by date */
GameList*  LastGameList; /* Points to the last listed game list. */

Game NULL_GAME = { /*.outcome=*/     0,
                  /*.date=*/        {0,0,0},
                  /*.homeTeam=*/    NULL,
                  /*.awayTeam=*/    NULL};
