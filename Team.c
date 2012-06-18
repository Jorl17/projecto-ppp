#include <assert.h>
#include <string.h>
#define ASSERT assert
#include "Team.h"
#include "TeamGameList.h"
#include "string.h"

int TeamGetPoints(Team* team) {
    list_t* tmp;
    ASSERT(team);
    /* If there isn't anything cached yet. */
    if (team->points==-1) {
        team->points=0;
        if (!team->gameList) {
            /* Since team->points != -1, TeamUpdateGameListCache will update
               the points for us.
              */
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

/*
  This code could be more efficient. It is like this because of a design failure
  that was only found really next to the deadline of the project (points weren't
  being kept for each game, just the outcome).
 */
void TeamPointsUpdateWithGame(Team* team, Game* game, bool remove) {
    int pts=0;
    uint8_t outcome;
    ASSERT(team);
    ASSERT(game);
    outcome = getOutcomeFromGame(game);
    if (game->homeTeam == team) {
        /* We play home */
        if ( outcome == OUTCOME_HOMEWIN)
            pts = 3;
        else if (outcome == OUTCOME_DRAW)
            pts = 1;
    } else {
        /* We play away */
        if ( outcome == OUTCOME_AWAYWIN)
            pts = 3;
        else if (outcome == OUTCOME_DRAW)
            pts = 1;
    }

    if (remove)
        team->points -=pts;
    else
        team->points +=pts;
}

void TeamUpdateGameListCache(Team* team, list_t* gameNode) {
    ASSERT(team);

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

Team* TeamFind(const char* _name) {
    int iMax=NUM_TEAMS-1, iMin=0, iMed, compare;
    char name[NAME_SIZE], copy[NAME_SIZE];
  
    strcpy(name, _name);
    toLower(name);
  
    while (iMax >= iMin) {
        iMed = (iMax + iMin) / 2;
        strcpy(copy, Teams[iMed].name);
        toLower(copy);
      
        compare = strcmp(copy ,name);
        if (compare < 0) /* A < B */
            iMin = iMed+1;
        else if (compare > 0) /* A > B */
            iMax = iMed-1;
        else
            return &Teams[iMed];
    }

    return NULL;
}
