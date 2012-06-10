#include <assert.h>
#define ASSERT assert
#include "Team.h"
#include "TeamGameList.h"

int TeamGetPoints(Team* team) {
    ASSERT(team);

    // If there isn't anything cached yet.
    if (team->points==-1) {
        if (!team->gameList) {
            team->points=0;
            TeamUpdateGameListCache(team, NULL);
        }
        /* Else: iterate the list and count points. FIXME! */
    }

    return team->points;
}

void TeamPointsUpdateWithGame(Team* team, Game* game) {
    ASSERT(team);
    ASSERT(game);

    if (game->homeTeam == team) {
        // We play home
        if ( game->outcome == OUTCOME_HOMEWIN)
            team->points += 3;
        else if (game->outcome == OUTCOME_DRAW)
            team->points += 1;
    } else {
        // We play away
        if ( game->outcome == OUTCOME_AWAYWIN)
            team->points += 3;
        else if (game->outcome == OUTCOME_DRAW)
            team->points += 1;
    }
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
                TeamGameListAdd(team->gameList, iter); /* FIXME: We could have a linear add function */
                if(team->points != -1)
                    TeamPointsUpdateWithGame(team, gamePtr);
            }
            iter = ListIterateNext(iter);
        }
    } else if (gameNode) {
        TeamGameListAdd(team->gameList, gameNode);
        if(team->points != -1)
            TeamPointsUpdateWithGame(team, GAMELIST_GAME(gameNode));
    }
    /* else we've been called to create it but it's already been created. */
}
