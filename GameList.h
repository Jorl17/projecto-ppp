#ifndef GAMELIST_H
#define GAMELIST_H 1
#include "datatypes.h"
struct _GameList {
    Game game;
    GameList* next;
    GameList* prev;
};
#endif
