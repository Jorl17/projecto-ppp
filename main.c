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

void cleanup(void) {
    size_t i;
    ListDelete(Games);
    for (i=0; i < NUM_TEAMS; i++)
        if (Teams[i].gameList)
            ListDeleteNoFreeData(Teams[i].gameList);
    if (ScoreboardList)
        ListDeleteNoFreeData(ScoreboardList);
    free(Teams);
}

int main(void) {
    char cmd[NAME_SIZE+1]={0};
    Team* selectedTeam;
    ScoreboardList = NULL;
    LastGameList = NULL;
    ClearScreen = false;
    ReadFiles();
  
    atexit(&cleanup); fflush(stdout);
    printf("Bem vindo ao administrador de campeonatos! Escreva \"ajuda\" para mais informação.\n");

    while(true) {
        do {
            printf("\n>>> ");; fflush(stdout);
        } while ( !readString(cmd, NAME_SIZE) );
        printf("\n");

        if ( strCaseEqual(cmd, "sair") )
            break;
        else if ( strCaseEqualn(cmd, "jogos", 5) ) {
            if (!cmd[5]) {
                LastGameList = NULL;
                ShowGames();
            } else if ( (selectedTeam = getTeamFromInput(&cmd[5])) != NULL ){
                TeamUpdateGameListCache(selectedTeam, NULL);
                LastGameList = selectedTeam->gameList;
                printf("Jogos da %s\n", selectedTeam->name);
                ShowGames();
            } else
                goto wrong_command;
        }
        else if ( strCaseEqual(cmd, "equipas") ) {
            ListTeams();
        }
        else if ( strCaseEqual(cmd, "novo") ) {
            NewGame();
        }
        else if ( strCaseEqualn(cmd, "apagar", 6) ) {
            DeleteGame(&cmd[6]);
        }
        else if ( strCaseEqual(cmd, "pontos") ) {
            ShowScoreboard();
        }
        else if (strCaseEqual(cmd, "limpeza")) {
            if (!ClearScreen) {
                ClearScreen = true;
                printf("Activada limpeza de ecra.\n");
            } else {
                ClearScreen = false;
                printf("Desactivada limpeza de ecra.\n");
            }
        }
        else if (strCaseEqual(cmd, "ajuda")) {
            if(ClearScreen)
                clearScreen();
            printf("Comandos:\n"
                   "equipas - lista todas as equipas do campeonato.\n"
                   "pontos - lista todas as equipas, ordenadas por classificação.\n"
                   "jogos - lista todos os jogos, por data.\n"
                   "jogos [x]  - lista todos os jogos, por data, da equipa [x], em que [x] é o nome da equipa.\n"
                   "novo - inicia a adicao de um novo jogo.\n"
                   "apagar [x] - apaga o jogo com o identificador [x] (da listagem mais recente).\n"
                   "limpeza - activa/desactiva a limpeza de ecra.\n"
                   "sair - Sai do programa.\n");
        }
        else {
            wrong_command:
            printf("Comando desconhecido. Talvez possa tentar \"ajuda\".\n");
        }

    }

    return 0;
}
