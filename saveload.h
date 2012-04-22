#ifndef SAVELOAD_H
#define SAVELOAD_H
#include "datatypes.h"

bool readFiles(void);

#define UPDATE_NEW_GAME 1
#define UPDATE_DEL_GAME 2
/**
  If type is UPDATE_NEW_GAME, updateGames() adds this game to the games file,
  adjusting any internal info stored in the file (ex: ids).
  If type is UPDATE_DEL_GAME, updateGames() deletes this game from the games file,
  adjusting any internal info stored in the file (ex: ids).

  The game that is going to be added/removed is passed as an argument.

  NOTE: Call this function before removing the game, so that it can still
  access the whole list to update the info.
  */
bool updateGames(uint8_t type, Game* game);
#endif /* SAVELOAD_H */
