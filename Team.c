#include <assert.h>
#define ASSERT assert
#include "Team.h"
#include "TeamGameList.h"

int TeamGetPoints(Team* team) {
    list_t* tmp;
    ASSERT(team);
    // If there isn't anything cached yet.
    if (team->points==-1) {
        team->points=0;
        if (!team->gameList) {
            TeamUpdateGameListCache(team, NULL);
        } else {
            tmp= team->gameList->next;
            while (!ListIsFooter(tmp)) {
                TeamPointsUpdateWithGame(team, GAMELIST_GAME(((list_t*)(tmp->data))), false);
                tmp = ListIterateNext(tmp);
            }
        }
    }

    return team->points;
}

void TeamPointsUpdateWithGame(Team* team, Game* game, bool remove) {
    int pts=0;
    ASSERT(team);
    ASSERT(game);
    if (game->homeTeam == team) {
        // We play home
        if ( game->outcome == OUTCOME_HOMEWIN)
            pts = 3;
        else if (game->outcome == OUTCOME_DRAW)
            pts = 1;
    } else {
        // We play away
        if ( game->outcome == OUTCOME_AWAYWIN)
            pts = 3;
        else if (game->outcome == OUTCOME_DRAW)
            pts = 1;
    }

    if (remove)
        team->points -=pts;
    else
        team->points +=pts;
}

void TeamUpdateGameListCache(Team* team, list_t* gameNode) {
    ASSERT(team);
    //ASSERT(gameNode); This can be NULL, in case we just want to create it once.

    if (!team->gameList) {
        list_t* iter = Games;
        Game* gamePtr;
        team->gameList = ListNew();
        iter = iter->next; /* Skip Header */
        while ( !ListIsFooter(iter) ) {
            gamePtr = GAMELIST_GAME(iter);
            if (gamePtr->awayTeam == team || gamePtr->homeTeam == team) {
                TeamGameListAppend(team->gameList, iter);
                if(team->points != -1)
                    TeamPointsUpdateWithGame(team, gamePtr, false);
            }
            iter = ListIterateNext(iter);
        }
    } else if (gameNode) {
        TeamGameListAdd(team->gameList, gameNode);
        if(team->points != -1)
            TeamPointsUpdateWithGame(team, GAMELIST_GAME(gameNode), false);
    }
    /* else we've been called to create it but it's already been created. */
}

void TeamDelGame(Team* team, Game* g) {
    if ( team->gameList ) {
        TeamGameListDelGame(team->gameList,g);
        if (team->points != -1)
            TeamPointsUpdateWithGame(team, g, true);
    }
}
