#ifndef TEAMGAMELIST_H
#define TEAMGAMELIST_H 1
#include "GameList.h"    /* list_t */


int compareDatesFromNodeAux(void* d1, void* d2);
list_t* TeamGameListAdd(list_t* list, list_t* g);
void TeamGameListDel(list_t* l);

#define TEAMGAMELIST_GAMELIST(list) LIST_DATA(list, GameList)
#endif /* TEAMGAMELIST_H */
