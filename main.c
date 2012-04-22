#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isdigit() */
#include "datatypes.h"

extern Team**     gTeams;        /* All teams, ordered alphabetically */
extern int        gNumTeams;     /* We don't have a const keyword...  */
extern GameList*  gGameList;     /* Has all games ordered by date */
extern GameList*  gLastGameList; /* Points to the last listed game list. */

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

bool isStrNumber(const char* s) {
    while ( *s ) {
        if (!isdigit(*(s++)))
                return false;
    }

    return true;
}

Team* getTeamFromInput(const char* input) {
    if ( isStrNumber(input) ) {
        int i = atoi(input);
        if ( i >= 0 && i < gNumTeams)
            return gTeams[i];
    }
    /* input must have the team name. implement a good searching algorithm here.
       Binary search? FIXME */

    /** If all else fails... */
    return NULL;
}

extern void doShowGames();      /** Make it explicit that they're defined elsewhere */
extern void doListTeams();      /** Make it explicit that they're defined elsewhere */
extern void doNewGame();        /** Make it explicit that they're defined elsewhere */
extern void doDeleteGame();     /** Make it explicit that they're defined elsewhere */
extern void doShowScoreboard(); /** Make it explicit that they're defined elsewhere */

int main(void) {
#define MAX_CMD 30
    char cmd[MAX_CMD];
    /*size_t cmdlen; NOT YET USED */
    Team* selectedTeam;

    while(true) {
        while ( !readString(cmd, MAX_CMD) ) ;

        /** QUIT **/
        if ( ! strcmp(cmd, "QUIT") )
            break;
        /** SHOW TEAMS and SHOW <TEAM> */
        else if ( !strcmp(cmd, "SHOW ") ) {
            if ( !strcmp(&cmd[5], "TEAMS") ) { /* 5 = strlen("SHOW "); */
                gLastGameList = gGameList;
                doShowGames(); /* FIXME: Pass remaining input? What for? */
            } else if ( (selectedTeam = getTeamFromInput(&cmd[5])) != NULL ){
                gLastGameList = selectedTeam->gameList;
                doShowGames(); /* FIXME: Pass remaining input? What for? */
            }
        }
        /** LIST **/
        else if ( !strcmp(cmd, "LIST") ) {
            doListTeams();
        }
        /** ADD GAME / CREATE / NEW / ADD ? FIXME, only one (or some) of these.**/
        else if ( !strcmp(cmd, "ADD GAME ") ) {
            doNewGame(&cmd[9]); /* 9 = strlen("ADD GAME") */
        }
        /** DEL GAME. FIXME: Some other name? */
        else if ( !strcmp(cmd, "DEL") ) {
            doDeleteGame(&cmd[3]); /* 3 = strlen("DEL") */
        }
        /** SCORE / SCOREBOARD. FIXME: Some other name? **/
        else if ( !strcmp(cmd, "SCORE") ) {
            doShowScoreboard();
        }

    }

    return 0;
}

