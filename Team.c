#include <assert.h>
#define ASSERT assert
#include "Team.h"

int TeamGetPoints(Team* team) {
    ASSERT(team);

    // If there isn't anything cached yet.
    if (team->points==-1) {
        if (!team->gameList)
            team->points = 0;
        else {
            // Traverse the list and gather points.
            GameList* l = team->gameList->next;
            team->points = 0;
            while(!GameListIsFooter(l)) {
                if (l->game.homeTeam == team) {
                    // We play home
                    if ( l->game.outcome == OUTCOME_HOMEWIN)
                        team->points += 3;
                    else if (l->game.outcome == OUTCOME_DRAW)
                        team->points += 1;
                } else {
                    // We play away
                    if ( l->game.outcome == OUTCOME_AWAYWIN)
                        team->points += 3;
                    else if (l->game.outcome == OUTCOME_DRAW)
                        team->points += 1;
                }
                l = GameListIterateNext(l);
            }
        }
    }

    return team->points;
}
