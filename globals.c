#include "datatypes.h"    // Team*
#include "GameList.h"     // GameList*
#include <stdlib.h>       // size_t

Team*      Teams;        // All teams, ordered alphabetically
size_t     NUM_TEAMS;
GameList*  Games;        // Has all games ordered by date
GameList*  LastGameList; // Points to the last listed game list.

Game NULL_GAME = {
	0, // outcome
    {0,0,0}, // date
    NULL, // home team
    NULL // home team
};
