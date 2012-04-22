#include "datatypes.h"

Team**     gTeams;        /* All teams, ordered alphabetically */
int        gNumTeams;     /* We don't have a const keyword...  */
GameList*  gGameList;     /* Has all games ordered by date */
GameList*  gLastGameList; /* Points to the last listed game list. */
