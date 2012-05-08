#ifndef SAVELOAD_H
#define SAVELOAD_H 1
#include "datatypes.h"     // Game*
#include "fixsizedtypes.h" // bool, uint8_t

bool readFiles(void);

#define ADD_GAME 1
#define DEL_GAME 2
/*
  On updateGames(), if type is:
	ADD_GAME - adds the game to the games file,
 	DEL_GAME - deletes the game from the games file

  The game in question is passed as an argument.
  NOTE: Call this function before removing the game, so that it can still
  access the whole list to update the info.
 */
bool updateGames(uint8_t type, Game* game);
#endif /* SAVELOAD_H */
