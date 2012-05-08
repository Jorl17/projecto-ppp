#ifndef TEAM_H
#define TEAM_H 1
#include "Team.h"
#include "GameList.h"
struct _Team {
    char name[NAME_SIZE];
    char location[NAME_SIZE];
    int cachedPoints; /* -1 indicates not cached yet */
    GameList* gameList; /* FIXME: What we want is a list of game pointers... */
};

int TeamGetPoints(Team* team);

extern Team*      Teams;        /* All teams, ordered alphabetically */
extern size_t     NUM_TEAMS;

#endif
