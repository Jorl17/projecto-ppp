#include <stdio.h>            // printf(), fflush()
#include <stdlib.h>           //  malloc(), free()
#include <string.h>           //  strcmp(), strncmp()
#include "string.h" //  readString()
#include "datatypes.h"        //  Team*
#include "Actions.h"          //  All actions
#include "GameList.h"         //  GameList, Game
#include "Team.h"
#include "TeamScoreBoardList.h"

int main(void) {
    char cmd[NAME_SIZE+1]={0};
    Team* selectedTeam;
    ScoreboardList = NULL;
    // size_t cmdlen; NOT YET USE

    while(true) {
        do {
            printf("What to do? "); fflush(stdout);
        } while ( !readString(cmd, NAME_SIZE) );

        // QUIT
        if ( ! strcmp(cmd, "QUIT") )
            break;
        // SHOW TEAMS and SHOW <TEAM>
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
        else if ( !strcmp(cmd, "LIST") ) {
            ListTeams();
        }
        else if ( !strncmp(cmd, "ADD", 3) ) {
            NewGame(&cmd[4]); // 4 = strlen("ADD ")
        }
        else if ( !strncmp(cmd, "DEL", 3) ) {
            DeleteGame(&cmd[3]); // 3 = strlen("DEL")
        }
        else if ( !strcmp(cmd, "SCORE") ) {
            ShowScoreboard();
        }
        else {
            wrong_command:
            printf("Unrecognized command.\n");
        }

    }

    return 0;
}
