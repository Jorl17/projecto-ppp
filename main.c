#include <stdio.h>            // printf(), fflush()
#include <stdlib.h>           //  malloc(), free()
#include <string.h>           //  strcmp(), strncmp()
#include "string.h" //  readString()
#include "datatypes.h"        //  Team*
#include "Actions.h"          //  All actions
#include "GameList.h"         //  GameList, Game
#include "Team.h"
#include "TeamScoreBoardList.h"
#include "saveload.h"

void showHelp() {
    printf("Command list:\n");
    printf("teams - lists all teams in the championship\n");
    printf("scores - lists all teams ordened by current score\n");
    printf("add - adds a game to the championship\n");
    printf("del - deletes a game from the championship\n");
    printf("quit or q - exit the program\n");
}

int main(void) {
    printf("Welcome to championship whack-a-mole!\nType \"help\" for more information.\n");
  
    char cmd[NAME_SIZE+1]={0};
    Team* selectedTeam;
    ScoreboardList = NULL;
    ReadTeams();

    while(true) {
        printf("\n>>> ");
        do {
            fflush(stdout);
        } while ( !readString(cmd, NAME_SIZE) );
        printf("\n");

        if ( ! strcmp(cmd, "q") || ! strcmp(cmd, "quit") ) {
            printf("Bye bye!");
            break;
        }
        else if ( !strncmp(cmd, "SHOW ", 5) ) {
            if ( !strcmp(&cmd[5], "TEAMS") ) { // 5 = strlen("SHOW ");
                LastGameList = NULL;
                ShowGames();
            } else if ( (selectedTeam = getTeamFromInput(&cmd[5])) != NULL ){
                TeamUpdateGameListCache(selectedTeam, NULL);
                LastGameList = selectedTeam->gameList;
                printf("TEAM: %s\n", selectedTeam->name); // FIXME: TESTING
                ShowGames();
            } else
                goto wrong_command; // FIXME: 'EVIL' GOTO!
        }
        else if ( !strcmp(cmd, "teams") ) {
            ListTeams();
        }
        else if ( !strncmp(cmd, "add", 3) ) {
            NewGame(&cmd[4]); // 4 = strlen("ADD ")
        }
        else if ( !strncmp(cmd, "del", 3) ) {
            DeleteGame(&cmd[3]); // 3 = strlen("DEL")
        }
        else if ( !strcmp(cmd, "scores") ) {
            ShowScoreboard();
        }
        else if ( !strcmp(cmd, "help") ) {
            showHelp();
        }
        else {
            wrong_command:
            printf("Unrecognized command.\n");
        }

    }

    return 0;
}
