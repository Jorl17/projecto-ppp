#include <stdio.h>    /* printf() */
#include <string.h>   /* strcmp() */
#include <assert.h>
#include "string_functions.h" /* isStrNumber(),readString() */
#include "datatypes.h"
#include "Team.h"
#include "GameList.h"
#include "Date.h"

#define ASSERT assert

Team* getTeamFromInput(const char* input) {
    int iMax=NUM_TEAMS-1, iMin=0, iMed, compare;
    if ( isStrNumber(input) ) {
        size_t i = (size_t)atoi(input);
        if (i < NUM_TEAMS)
            return &Teams[i];
    }
    /* input must have the team name. FIXME. Trim string (remove whitespace)*/
    while (iMax >= iMin) {
        iMed = (iMax + iMin) / 2;
        compare = strcmp(Teams[iMed].name,input);
        if (compare < 0) /* A < B */
            iMin = iMed+1;
        else if (compare > 0) /* A > B */
            iMax = iMed-1;
        else
            return &Teams[iMed];
    }

    /** If all else fails... **/
    return NULL;
}

void printGame(unsigned int id, Game* game) {
    /* FIXME: This is only a very raw prototype */
    ASSERT(game);
    printf("%u. ", id);
    printDate(game->date, false);
    printf(": %s vs %s:\t", game->homeTeam->name, game->awayTeam->name);

    if (game->outcome == OUTCOME_HOMEWIN)
        printf("Vitória da Casa\n");
    else if (game->outcome == OUTCOME_AWAYWIN)
        printf("Empate\n");
    else
        printf("Derrota da Casa\n");
}

void ShowGames(void) {
    GameList* local;
    size_t c=0;
    ASSERT(LastGameList);
    local = LastGameList->next;
    while(local->next) {
        printGame(c++, &(local->game));
        local = local->next;
    }
}

void ListTeams(void) {
    size_t i, len, j;
    /*               30 characters                   30 characters      Right aligned */
    printf("_____________________________________________________________________________\n"
           "| id |            Nome              |          Localidade          | Pontos |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    for (i=0; i < NUM_TEAMS; i++) {
        printf("|%-4lu", i);
        /** Print Name centered **/
        printf("|");
        len = strlen(Teams[i].name);
        for (j = 1; j <= (30-len)/2; j++)
            printf(" ");
        printf("%s", Teams[i].name);
        j+=len;
        for (; j <= 30; j++)
            printf(" ");

        /** Print location centered **/
        printf("|");
        len = strlen(Teams[i].location);
        for (j = 1; j <= (30-len)/2; j++)
            printf(" ");
        printf("%s", Teams[i].location);
        j+=len;
        for (; j <= 30; j++)
            printf(" ");

        /** Print points right aligned with 1 space to the left and to the right **/
        printf("| %6d ", Teams[i].points); /* Fixme, hacked in for testing. We need a TeamGetPoints() that sets up cache and all that */
        printf("|\n");
    }

    printf("------------------------------------------------------------------------------\n");
}

void NewGame(const char* input) {
    Game game;
    size_t read;
    char str[NAME_SIZE];
    if (*input) {
        /* User probably passed in the data through the commandline */
        /* FIXME */
    } else {
        game.date=getDateFromUser("Data do jogo?");
        if (!compareDates(game.date,DATEMIN)) /* If they're equal, then compareDates returns 0 */
            return ;

        printf("Equipa da Casa? "); fflush(stdout);
        read = readString(str, NAME_SIZE);
        if (!read)
            return ;

        else if ( ! (game.homeTeam = getTeamFromInput(str)) )
            return ;

        printf("Equipa Visitante? "); fflush(stdout);
        read = readString(str, NAME_SIZE);
        if (!read)
            return ;

        else if ( ! (game.awayTeam = getTeamFromInput(str)) )
            return ;

        if (game.awayTeam==game.homeTeam)
            return ;

        printf("Resultado (V, E, D)? "); fflush(stdout);
        read = readString(str, 2);
        if (*str=='V' || *str == 'v')
            game.outcome = OUTCOME_HOMEWIN;
        else if (*str=='E' || *str == 'e')
            game.outcome = OUTCOME_DRAW;
        else if (*str=='D' || *str == 'd')
            game.outcome = OUTCOME_AWAYWIN;
        else
            return ;

    }

    printGame(0, &game); /* Just here to test. Dummy ID */

    GameListAddGame(Games, game);
    /* create and call functions here:
      TeamUpdateGameListCache(), which will update the game list cache if needed.
      */

}
void DeleteGame(const char* input) {printf("DeleteGame() called with '%s'\n", input);}
void ShowScoreboard(void) {}
