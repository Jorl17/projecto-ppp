#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isdigit() */
#include "datatypes.h"
#include "GameList.h"
/** Temporary assert stuff, until we move some code in main to other areas **/
#include <assert.h>
#define ASSERT assert

extern Team*      Teams;        /* All teams, ordered alphabetically */
extern int        NumTeams;     /* We don't have a const keyword...  */
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
    int iMax=0, iMin=0, iMed;
    if ( isStrNumber(input) ) {
        int i = atoi(input);
        if ( i >= 0 && i < NumTeams)
            return &Teams[i];
    }
    /* input must have the team name. FIXME. Trim string (remove whitespace)*/
    while (iMax >= iMin) {
        iMed = (iMax + iMin) / 2;
        if (Teams[iMed].name < input)
            iMin = iMed+1;
        else if (Teams[iMed].name > input)
            iMax = iMed-1;
        else
            return &Teams[iMed];
    }


    /** If all else fails... */
    return NULL;
}

void printGame(unsigned int id, Game* game) {
    ASSERT(game); ASSERT(game->homeTeam); ASSERT(game->awayTeam);
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
    GameList* local = LastGameList;
    size_t c=0;
    while(local->next) {
        printGame(c++, &local->game);
        local = local->next;
    }
}
void doListTeams(void) {}
void doNewGame(const char* input) {printf("doNewGame() called with '%s'\n", input);}
void doDeleteGame(const char* input) {printf("doDeleteGame() called with '%s'\n", input);}
void doShowScoreboard(void) {}
#endif
int main(void) {
#define MAX_CMD 30
    char cmd[MAX_CMD];
    /*size_t cmdlen; NOT YET USED */
    Team* selectedTeam;

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
                doShowGames(); /* FIXME: Pass remaining input? What for? */
            } else if ( (selectedTeam = getTeamFromInput(&cmd[5])) != NULL ){
                LastGameList = selectedTeam->gameList;
                doShowGames(); /* FIXME: Pass remaining input? What for? */
            }
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
        /** Unrecognized command */
        else {
            printf("Unrecognized command.\n");
        }

    }

    return 0;
}

