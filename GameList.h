#ifndef GAMELIST_H
#define GAMELIST_H 1
#include "fixsizedtypes.h" /* bool */
#include "datatypes.h" /* GameList*, Game* (both forward declared) */
#include "Team.h"      /* Team* */
#include "Date.h"      /* Date */
#define OUTCOME_HOMEWIN 1
#define OUTCOME_DRAW    2
#define OUTCOME_AWAYWIN 3
struct _Game {
    uint8_t outcome;
    Date date;
    Team* homeTeam;
    Team* awayTeam;
};

struct _GameList {
    Game game;
    GameList* next;
    GameList* prev;
};

GameList* GameListNew(void);
void GameListDelete(GameList* list);
void GameListAddGame(GameList* list, Game g);
void GameListDelGame(GameList* list);
void GameListDelete(GameList* list);
GameList* GameListIterateNext(GameList* list);
GameList* GameListIteratePrev(GameList* list);
bool GameListIsHeader(GameList* list);
bool GameListIsFooter(GameList* list);


extern GameList*  Games;        /* Has all games ordered by date */
extern GameList*  LastGameList; /* Points to the last listed game list. */
extern Game NULL_GAME;
#endif
