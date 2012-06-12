#include "TeamScoreBoardList.h"
#include "Team.h"
#include "fixsizedtypes.h"
#include <assert.h>
#define ASSERT assert

int compareTeamsByPointsAux(void* d1, void* d2) {
    int pts1, pts2;
    pts1 = TeamGetPoints((Team*)d1);
    pts2 = TeamGetPoints((Team*)d2);

    return pts2-pts1;
}

int compareTeamsAux(void* d1, void* d2) {

    if (d1==d2)
        return 0;
    else
        return -1;
}

/*
  Must be called AFTER the game has been removed.
  */
list_t* ScoreboardListUpdate(list_t* list, Game* game) {
    if (!list) {
        size_t i;
        /* Create it */
        list = ListNew();
        for (i=0; i < NUM_TEAMS; i++)
            ListAdd(list, (void*)&Teams[i], &compareTeamsByPointsAux);
    } else if (game) {
        Team* homeTeam;
        Team* awayTeam;
        list_t* tmpNode;
        /* Find the teams in game and readd them */
        ASSERT(game->homeTeam);
        ASSERT(game->awayTeam);
        homeTeam = game->homeTeam;
        awayTeam = game->awayTeam;

        tmpNode = ListSearch(list, (void*)homeTeam, &compareTeamsAux);
        ASSERT(tmpNode);
        ASSERT(((Team*)tmpNode->data) == homeTeam);
        ScoreboardListDel(tmpNode);
        ListAdd(list, homeTeam, &compareTeamsByPointsAux);

        tmpNode = ListSearch(list, (void*)awayTeam, &compareTeamsAux);
        ASSERT(tmpNode);
        ASSERT(((Team*)tmpNode->data) == awayTeam);
        ScoreboardListDel(tmpNode);
        ListAdd(list, awayTeam, &compareTeamsByPointsAux);
    }
    return list;
}

void ScoreboardListDel(list_t* l) {
    ASSERT(l);
    l->prev->next = l->next;
    l->next->prev = l->prev;
    free(l);
}
