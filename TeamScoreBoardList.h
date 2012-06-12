#ifndef TEAMSCCOREBOARDLIST_H
#define TEAMSCCOREBOARDLIST_H 1
#include "GameList.h"    /* list_t */


int compareTeamsAux(void* d1, void* d2);
int compareTeamsByPointAux(void* d1, void* d2);
void ScoreboardListDel(list_t* l);
list_t* ScoreboardListUpdate(list_t* list, Game* game);

extern list_t*  ScoreboardList;
#endif /* TEAMSCCOREBOARDLIST_H */
