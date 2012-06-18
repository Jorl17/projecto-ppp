#include <stdlib.h>     /* malloc() */
#include "datatypes.h"
#include "GameList.h"
#include "Date.h"       /* compareDates() */
#include "list_t.h"
#include "Team.h"
#include "TeamGameList.h"
#include "ScoreBoardList.h"
#include "assert.h"
#include "saveload.h"

#define ASSERT assert
int compareDatesAux(void* d1, void* d2) {
    return compareDates(((Game*)d1)->date, ((Game*)d2)->date);
}

list_t* GameListAddGame(list_t* list, Game game, bool update) {
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

    /* Update file FIXME */
    if(update)
        WriteGames();
    return tmp;
}
uint8_t getOutcomeFromGame(Game* g) {
    ASSERT(g);
    if (g->homePoints > g->awayPoints)
        return OUTCOME_HOMEWIN;
    else if (g->homePoints < g->awayPoints)
        return OUTCOME_AWAYWIN;
    else
        return OUTCOME_DRAW;
}
