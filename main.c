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

#if 0
extern void doShowGames(void);      /** Make it explicit that they're defined elsewhere */
extern void doListTeams(void);
extern void doNewGame(const char*);
extern void doDeleteGame(const char*);
extern void doShowScoreboard(void);
#else
void doShowGames(void) {}
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

