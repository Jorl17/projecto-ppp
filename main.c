#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isdigit() */
#include "datatypes.h"
#include "GameList.h"
/** Temporary assert stuff, until we move some code in main to other areas **/
#include <assert.h>
#define ASSERT assert

/* FIXME: Where to put this? */
extern Team*      Teams;        /* All teams, ordered alphabetically */
extern size_t     NumTeams;     /* We don't have a const keyword...  */
extern GameList*  Games;        /* Has all games ordered by date */
extern GameList*  LastGameList; /* Points to the last listed game list. */

/***
  Reads a string from standard input. Returns the length of the string or 0
  if there was an error.
*/
size_t readString(char* str, size_t maxlen) {
    size_t len;
    if ( ! fgets(str, maxlen, stdin) )
        return 0;

    len = strlen(str);
    str[len-1]='\0';
    return len;
}

/*
  Checks if a string is a number.
 */
bool isStrNumber(const char* s) {
    while ( *s ) {
        if (!isdigit(*(s++)))
                return false;
    }

    return true;
}

Team* getTeamFromInput(const char* input) {
    int iMax=NumTeams-1, iMin=0, iMed, compare;
    if ( isStrNumber(input) ) {
        size_t i = (size_t)atoi(input);
        if (i < NumTeams)
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
    printf(": %s -- %s:\t", game->homeTeam->name, game->awayTeam->name);

    if (game->outcome == OUTCOME_HOMEWIN)
        printf("Home Win\n");
    else if (game->outcome == OUTCOME_AWAYWIN)
        printf("Away Win\n");
    else
        printf("Draw\n");
}

#if 0
extern void doShowGames(void);      /** Make it explicit that they're defined elsewhere */
extern void doListTeams(void);
extern void doNewGame(const char*);
extern void doDeleteGame(const char*);
extern void doShowScoreboard(void);
#else
void doShowGames(void) {
    ASSERT(LastGameList);
    GameList* local = LastGameList->next;
    size_t c=0;
    while(local->next) {
        printGame(c++, &(local->game));
        local = local->next;
    }
}

void doListTeams(void) {
    size_t i, len, j;
    /*               30 characters                   30 characters      Right aligned */
    printf("_____________________________________________________________________________\n"
           "| id |            Nome              |          Localidade          | Pontos |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    for (i=0; i < NumTeams; i++) {
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
        printf("| %6d ", Teams[i].cachedPoints); /* Fixme, hacked in for testing. We need a TeamGetPoints() that sets up cache and all that */
        printf("|\n");
    }

    printf("------------------------------------------------------------------------------\n");
}
void doNewGame(const char* input) {printf("doNewGame() called with '%s'\n", input);}
void doDeleteGame(const char* input) {printf("doDeleteGame() called with '%s'\n", input);}
void doShowScoreboard(void) {}
#endif
int main(void) {
#define MAX_CMD 30
    char cmd[MAX_CMD];
    /*size_t cmdlen; NOT YET USED */

    /******************************** TESTING STUFF *******************************/
    Team* selectedTeam;
    Teams = (Team*)malloc(3*sizeof(Team));
    strcpy(Teams[0].name, "AB Porto");
    strcpy(Teams[0].location, "Porto, Portugal");
    Teams[0].cachedPoints = 64;

    strcpy(Teams[1].name, "BE Benfica");
    strcpy(Teams[1].location, "Lisboa, Portugal");
    Teams[1].cachedPoints = 32;

    strcpy(Teams[2].name, "CD Braga");
    strcpy(Teams[2].location, "Braga, Portugal");
    Teams[2].cachedPoints = 63;
    NumTeams = 3;
    Games = GameListNew();
    /** This stuff triggers ANSI C pedantic warnings, but it's in the testing
      part, so it's ok.**/
    Game game1 = { /*.outcome=*/     OUTCOME_HOMEWIN,
                      /*.date=*/        {5,5,1993},
                   /*.homeTeam=*/    &Teams[0],
                   /*.awayTeam=*/    &Teams[1]};
    Game game2 = { /*.outcome=*/     OUTCOME_AWAYWIN,
                      /*.date=*/        {4,5,1993},
                   /*.homeTeam=*/    &Teams[0],
                   /*.awayTeam=*/    &Teams[1]};
    Game game3 = { /*.outcome=*/     OUTCOME_DRAW,
                      /*.date=*/        {5,5,1993},
                   /*.homeTeam=*/    &Teams[2],
                   /*.awayTeam=*/    &Teams[1]};
    Game game4 = { /*.outcome=*/     OUTCOME_HOMEWIN,
                      /*.date=*/        {7,5,1993},
                   /*.homeTeam=*/    &Teams[0],
                   /*.awayTeam=*/    &Teams[1]};
    Game game5 = { /*.outcome=*/     OUTCOME_HOMEWIN,
                      /*.date=*/        {2,5,1993},
                   /*.homeTeam=*/    &Teams[0],
                   /*.awayTeam=*/    &Teams[1]};
    LastGameList = Games;
    GameListAddGame(Games, game1);
    doShowGames(); printf("\n");
    GameListAddGame(Games, game2);
    doShowGames();printf("\n");
    GameListAddGame(Games, game3);
    doShowGames();printf("\n");
    GameListAddGame(Games, game4);
    doShowGames();printf("\n");
    GameListAddGame(Games, game5);
    doShowGames();printf("\n");
    /******************************* !TESTING STUFF *******************************/

    while(true) {
        printf("What to do? "); fflush(stdout);
        while ( !readString(cmd, MAX_CMD) ) ;

        /** QUIT **/
        if ( ! strcmp(cmd, "QUIT") )
            break;
        /** SHOW TEAMS and SHOW <TEAM> */
        else if ( !strncmp(cmd, "SHOW ", 5) ) {
            if ( !strcmp(&cmd[5], "TEAMS") ) { /* 5 = strlen("SHOW "); */
                LastGameList = Games;
                doShowGames();
            } else if ( (selectedTeam = getTeamFromInput(&cmd[5])) != NULL ){
                LastGameList = selectedTeam->gameList;
                printf("TEAM: %s\n", selectedTeam->name); /* FIXME: TESTING */
                doShowGames();
            } else
                goto wrong_command; /*FIXME: 'EVIL' GOTO!*/
        }
        /** LIST **/
        else if ( !strcmp(cmd, "LIST") ) {
            doListTeams();
        }
        /** ADD GAME / CREATE / NEW / ADD ? FIXME, only one (or some) of these.**/
        else if ( !strncmp(cmd, "ADD", 3) ) {
            doNewGame(&cmd[4]); /* 4 = strlen("ADD ") */
        }
        /** DEL GAME. FIXME: Some other name? */
        else if ( !strcmp(cmd, "DEL") ) {
            doDeleteGame(&cmd[3]); /* 3 = strlen("DEL") */
        }
        /** SCORE / SCOREBOARD. FIXME: Some other name? **/
        else if ( !strcmp(cmd, "SCORE") ) {
            doShowScoreboard();
        }
        /** Unrecognized command **/
        else {
            wrong_command:
            printf("Unrecognized command.\n");
        }

    }

    /******************************** TESTING STUFF *******************************/
    GameListDelete(Games);
    free(Teams);
    /******************************* !TESTING STUFF *******************************/

    return 0;
}

