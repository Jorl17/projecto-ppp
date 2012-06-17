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
    ClearScreen = true;
    atexit(&cleanup);
    printf("A ler ficheiros de dados..."); fflush(stdout);
    ReadFiles();
    printf("pronto!\n");

    while(true) {
        do {
            printf("O que fazer? "); fflush(stdout);
        } while ( !readString(cmd, NAME_SIZE) );

        if ( strCaseEqual(cmd, "SAIR") )
            break;
        else if ( strCaseEqualn(cmd, "JOGOS", 5) ) {
            if (!cmd[5]) {
                LastGameList = NULL;
                ShowGames();
            } else if ( (selectedTeam = getTeamFromInput(&cmd[5])) != NULL ){
                TeamUpdateGameListCache(selectedTeam, NULL);
                LastGameList = selectedTeam->gameList;
                printf("EQUIPA: %s\n", selectedTeam->name);
                ShowGames();
            } else
                goto wrong_command;
        }
        else if ( strCaseEqual(cmd, "EQUIPAS") ) {
            ListTeams();
        }
        else if ( strCaseEqual(cmd, "NOVO") ) {
            NewGame();
        }
        else if ( strCaseEqualn(cmd, "APAGAR", 6) ) {
            DeleteGame(&cmd[6]);
        }
        else if ( strCaseEqual(cmd, "CLASS") ) {
            ShowScoreboard();
        }
        else if (strCaseEqual(cmd, "LIMP")) {
            if (!ClearScreen) {
                ClearScreen = true;
                printf("Activada limpeza de ecra.\n");
            } else {
                ClearScreen = false;
                printf("Desactivada limpeza de ecra.\n");
            }
        }
        else if (strCaseEqual(cmd, "AJUDA")) {
            if(ClearScreen)
                clearScreen();
            printf("Comandos:\n"
                   "SAIR       -- Sai do programa.\n"
                   "EQUIPAS    -- Lista equipas ordenadas alfabeticamente.\n"
                   "JOGOS      -- Lista todos os jogos, por data.\n"
                   "JOGOS [x]  -- Lista todos os jogos, por data, da equipa [x], em que [x] pode ser ou seu nome ou o seu id.\n"
                   "CLASS      -- Mostra a classificacao das equipas.\n"
                   "NOVO       -- Inicia a adicao de um novo jogo.\n"
                   "APAGAR     -- Inicia a adicao de um novo jogo.\n"
                   "APAGAR [x] -- Apaga o jogo com o id [x] (da listagem mais recente).\n"
                   "LIMP       -- Activa/Desactiva a limpeza de ecra aquando de um comando..\n\n");
        }
        else {
            wrong_command:
            printf("Comando desconhecido. Talvez possa tentar AJUDA.\n");
        }

    }

    return 0;
}
