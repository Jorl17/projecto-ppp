#include <stdio.h>    /* printf() */
#include <string.h>   /* strcmp() */
#include <assert.h>
#include "string.h" /* isStrNumber(),readString() */
#include "datatypes.h"
#include "Team.h"
#include "GameList.h"
#include "Date.h"
#include "TeamScoreBoardList.h"

#define ASSERT assert

Team* getTeamFromInput(const char* input) {
    int iMax=NUM_TEAMS-1, iMin=0, iMed, compare;
    ASSERT(input);
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

void printGame(size_t id, Game* game) {
    size_t j, len;
    ASSERT(game); ASSERT(game->homeTeam); ASSERT(game->awayTeam);
    ASSERT(compareDates(game->date,DATEMIN)); ASSERT(compareDates(game->date,DATEMAX));
    ASSERT(game->outcome == OUTCOME_HOMEWIN || game->outcome == OUTCOME_AWAYWIN || game->outcome == OUTCOME_DRAW);
    printf("|%-4lu", id);
    /** Print Home Team Name centered **/
    printf("|");
    len = strlen(game->homeTeam->name);
    for (j = 1; j <= (30-len)/2; j++)
        printf(" ");
    printf("%s", game->homeTeam->name);
    j+=len;
    for (; j <= 30; j++)
        printf(" ");

    if (game->outcome == OUTCOME_HOMEWIN)
        printf("|V    D|");
    else if (game->outcome == OUTCOME_AWAYWIN)
        printf("|D    V|");
    else
        printf("|E    E|");

    /** Print Away Team Name centered **/
    len = strlen(game->awayTeam->name);
    for (j = 1; j <= (30-len)/2; j++)
        printf(" ");
    printf("%s", game->awayTeam->name);
    j+=len;
    for (; j <= 30; j++)
        printf(" ");

    /** Print date **/
    printf("| ");
    printDate(game->date, false);
    printf(" |\n");
}

void ShowGames(void) {
    list_t* local;
    size_t c=0;
    printf("________________________________________________________________________________________\n"
           "| id |        Equipa da Casa        | Res. |       Equipa Visitante       |    Data    |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^|\n");
    /* ex:  |1   |           FC Porto           |V    D|           SL Bosta           |  3/ 4/1994 |\n); */
    if (LastGameList == NULL) {
        local = Games->next;
        while(local->next) {
            printGame(c++, local->data);
            local = local->next;
        }
    } else {
        if (LastGameList->next) {
            local = LastGameList->next;
            while(local->next) {
                printGame(c++, ((Game*)((list_t*)local->data)->data));
                local = local->next;
            }
        }
    }
    printf("----------------------------------------------------------------------------------------\n");
}

void TablePrintTeam(size_t i, Team* t) {
    size_t j, len;
    printf("|%-4lu", i);
    /** Print Name centered **/
    printf("|");
    len = strlen(t->name);
    for (j = 1; j <= (30-len)/2; j++)
        printf(" ");
    printf("%s", t->name);
    j+=len;
    for (; j <= 30; j++)
        printf(" ");

    /** Print location centered **/
    printf("|");
    len = strlen(t->location);
    for (j = 1; j <= (30-len)/2; j++)
        printf(" ");
    printf("%s", t->location);
    j+=len;
    for (; j <= 30; j++)
        printf(" ");

    /** Print points right aligned with 1 space to the left and to the right **/
    printf("| %6d ", TeamGetPoints(t));
    printf("|\n");
}

void ListTeams(void) {
    size_t i;
    /*               30 characters                   30 characters      Right aligned */
    printf("_____________________________________________________________________________\n"
           "| id |            Nome              |          Localidade          | Pontos |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    for (i=0; i < NUM_TEAMS; i++) {
        TablePrintTeam(i, &Teams[i]);
    }

    printf("------------------------------------------------------------------------------\n");
}

void NewGame(const char* input) {
    Game game;
    size_t read;
    char str[NAME_SIZE];
    list_t* tmp;
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

        printf("Resultado (V, E, D da casa)? "); fflush(stdout);
        read = readString(str, 2);
        if (*str=='V' || *str == 'v')
            game.outcome = OUTCOME_HOMEWIN;
        else if (*str=='E' || *str == 'e')
            game.outcome = OUTCOME_DRAW;
        else if (*str=='D' || *str == 'd')
            game.outcome = OUTCOME_AWAYWIN;
        else
            return ;

        printf("Jogo adicionado!\n");
    }

    printGame(0, &game); /* Just here to test. Dummy ID FIXME*/

    tmp=GameListAddGame(Games, game);

}
void DeleteGame(const char* input) {
    list_t* iter;
    Game* g;
    size_t i=0, id;
    ASSERT(input);
    if (!*input)
      ;/* FIXME:Fetch the input */
    else
        id = atoi(input); /*FIXME: Error checking here. */
    if (LastGameList == NULL) {
        iter = Games->next;
        while (!ListIsFooter(iter)) {
            if (i++==id)
                break;
            iter = ListIterateNext(iter);
        }

        /* FIXME: Update files here, after removing the game */
        g = GAMELIST_GAME(iter);
        ASSERT(g->homeTeam);
        ASSERT(g->awayTeam);
        TeamDelGame(g->homeTeam, g);
        TeamDelGame(g->awayTeam, g);
        ListDel(iter); /* This effectively DELETES the game from memory */
    } else {
        list_t* tmp;
        iter = LastGameList->next;
        while (!ListIsFooter(iter)) {
            if (i++==id)
                break;
            iter = ListIterateNext(iter);
        }
        tmp = (list_t*)iter->data;
        g = GAMELIST_GAME(tmp);
        printGame(0, g);
        ASSERT(g->homeTeam);
        ASSERT(g->awayTeam);
        TeamDelGame(g->homeTeam, g);
        TeamDelGame(g->awayTeam, g);
        ListDel(tmp); /* The cool thing here is that tmp is already the ponter to the node!! */
    }
    /* Go to the id-th game in the current gameList (LastGameList or Game if LastGameList==NULL */
    /* If indeed LastGameList != NULL, remove the game from the list and remove it from the TeamGameLists */
    /* Otherwise, remove it from the list and make sure that the teams are also adjusted. (The difference here is that we must search the game in each team's gameList) */

}
void ShowScoreboard(void) {
    list_t* tmp;
    int i=1;
    ScoreboardList = ScoreboardListUpdate(ScoreboardList, NULL);
    tmp = ScoreboardList->next; /* Jump over header. FIXME: Need function for this */

    printf("_____________________________________________________________________________\n"
           "| id |            Nome              |          Localidade          | Pontos |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    while (!ListIsFooter(tmp)) {
        TablePrintTeam(i++, (Team*)tmp->data);
        tmp = ListIterateNext(tmp);
    }
    printf("-----------------------------------------------------------------------------\n");
}
