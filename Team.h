#ifndef TEAM_H
#define TEAM_H 1
#include "GameList.h"
struct _Team {
    char name[NAME_SIZE];
    char location[NAME_SIZE];
    int index;
    int points; // -1 indicates not cached yet
    list_t* gameList;
};

void TeamPointsUpdateWithGame(Team* team, Game* game, bool remove);
void TeamUpdateGameListCache(Team* team, list_t* gameNode);
int TeamGetPoints(Team* team);
void TeamDelGame(Team* team, Game* g);

extern Team*      Teams;        /* All teams, ordered alphabetically */
extern size_t     NUM_TEAMS;

#endif
