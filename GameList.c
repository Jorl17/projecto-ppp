#include <stdlib.h>     /* malloc() */
#include "datatypes.h"
#include "GameList.h"
#include "Date.h"       /* compareDates() */
#include "list_t.h"
#include "Team.h"
#include "TeamGameList.h"
#include "TeamScoreBoardList.h"
int compareDatesAux(void* d1, void* d2) {
    return compareDates(((Game*)d1)->date, ((Game*)d2)->date);
}

list_t* GameListAddGame(list_t* list, Game game) {
    Game* g = malloc(sizeof(Game));
    list_t* tmp;
    *g = game;
    tmp=ListAdd(list, (void*)g, &compareDatesAux);
    if (g->homeTeam->gameList)
        TeamUpdateGameListCache(g->homeTeam, tmp);
    if (g->awayTeam->gameList)
        TeamUpdateGameListCache(g->awayTeam, tmp);

    if(ScoreboardList)
        ScoreboardList = ScoreboardListUpdate(ScoreboardList, g);
    return tmp;
}
