#ifndef DATATYPES_H
#define DATATYPES_H 1
#include "fixsizedtypes.h"
#include "Date.h"

/****** Forward declare a couple of things until we have implemented them *****/
typedef struct _GameList GameList;
typedef struct _Team     Team;
typedef struct _Game     Game;
/***** !Forward declare a couple of things until we have implemented them *****/

#define OUTCOME_HOMEWIN 1
#define OUTCOME_DRAW    2
#define OUTCOME_AWAYWIN 3
struct _Game {
    uint8_t outcome;
    Date date;
    int cachedPoints; /* Cached points. -1 indicates not cached yet */
    Team* homeTeam;
    Team* awayTeam;
};
extern Game nullGame;

#define MAX_TEAM_NAME 30
#define MAX_LOC_NAME  30
struct _Team {
    char name[MAX_TEAM_NAME];
    char location[MAX_LOC_NAME];
    GameList* gameList;
};

struct _GameList {
    Game game;
    GameList* next;
    GameList* prev;
};

#endif /* DATATYPES_H */
