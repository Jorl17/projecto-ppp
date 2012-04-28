#ifndef DATATYPES_H
#define DATATYPES_H 1
#include "fixsizedtypes.h"
#include "Date.h"

#define OUTCOME_HOMEWIN 1
#define OUTCOME_DRAW    2
#define OUTCOME_AWAYWIN 3
#define NAME_SIZE 30

typedef struct _GameList GameList;
typedef struct _Team     Team;
typedef struct _Game     Game;

struct _Team {
    char name[NAME_SIZE];
    char location[NAME_SIZE];
    int cachedPoints; /* -1 indicates not cached yet */
    GameList* gameList;
};

extern Team*      Teams;        /* All teams, ordered alphabetically */
extern size_t     NUM_TEAMS;

#endif /* DATATYPES_H */
