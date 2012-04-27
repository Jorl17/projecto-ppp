#ifndef GAMELIST_H
#define GAMELIST_H 1
#include "datatypes.h"
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
#endif
