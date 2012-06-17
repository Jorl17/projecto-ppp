#include "datatypes.h"    // Team*
#include "GameList.h"     // GameList*
#include <stdlib.h>       // size_t

size_t   NUM_TEAMS;
Team*    Teams;         // All teams, ordered alphabetically
list_t*  Games;         // Has all games ordered by date
list_t*  LastGameList;  // Points to the last listed game list.
list_t*  ScoreboardList; // Has teams in scoreboard order
bool     ClearScreen;   // Should we clear the screen some times?

Game NULL_GAME = {
    0, 0,// outcome
    {0,0,0}, // date
    NULL, // home team
    NULL // home team
};
