#include "datatypes.h"    // Team*
#include "GameList.h"     // GameList*
#include <stdlib.h>       // size_t

int     NUM_TEAMS;
Team*      Teams;        // All teams, ordered alphabetically
GameList*  Games;        // Has all games ordered by date
<<<<<<< HEAD
GameList*  LastGameList; // Points to the last listed game list. FIXME: This is not the right type. */

=======
GameList*  LastGameList; // Points to the last listed game list
>>>>>>> Jaliborc

GameList NULL_GAME_LIST = {};
Game NULL_GAME = {
    0, // outcome
    {0,0,0}, // date
    NULL, // home team
    NULL // home team
};
