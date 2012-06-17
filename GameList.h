#ifndef GAMELIST_H
#define GAMELIST_H 1
#include "fixsizedtypes.h" /* bool */
#include "datatypes.h" /* GameList*, Game* (both forward declared) */
#include "Date.h"      /* Date */
#include "list_t.h"    /* list_t */
#include "Team.h"      /* Team* */
#define OUTCOME_HOMEWIN 1
#define OUTCOME_DRAW    2
#define OUTCOME_AWAYWIN 3

struct _Game {
    uint8_t homePoints;
    uint8_t awayPoints;
    Date date;
    Team* homeTeam;
    Team* awayTeam;
};

int compareDatesAux(void* d1, void* d2);

list_t* GameListAddGame(list_t* list, Game g);

uint8_t getOutcomeFromGame(Game* g);

extern list_t*  Games;        /* Has all games ordered by date */
extern list_t*  LastGameList; /* Points to the last listed game list. FIXME: it isn't a GameList*/
extern Game NULL_GAME;

#define GAMELIST_GAME(list) LIST_DATA(list, Game)
#endif
