#include <stdio.h>    /* printf() */
#include <string.h>   /* strcmp() */
#include <assert.h>
#include "string.h" /* isStrNumber(),readString() */
#include "datatypes.h"
#include "Team.h"
#include "GameList.h"
#include "Date.h"
#include "TeamScoreBoardList.h"
#include "saveload.h"
#include "Actions.h"

#define ASSERT assert

void clearScreen(void) {
#if !defined(CLRSCRN_STANDARD) && (defined(__unix__) || defined(unix) || defined(__unix) || defined (__linux) || defined(__linux__) || defined(linux))
    system("clear");
#elif !defined(CLRSCRN_STANDARD) && (defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(__WINDOWS__) || defined(__TOS_WIN__))
    system("cls");
#else
    size_t i;
    for (i=0; i < 80; i++)
        printf("\n");
#endif
}

Team* getTeamFromInput(char* input) {
    ASSERT(input);
    if ( isStrNumber(input) ) {
        size_t i = (size_t)atoi(input);
        if (i < NUM_TEAMS)
            return &Teams[i];
    }
    /* input must have the team name.*/
    trimString(input);
    return TeamFind(input);
}

void printGame(size_t id, Game* game) {
    size_t j, len;
    ASSERT(game); ASSERT(game->homeTeam); ASSERT(game->awayTeam);
    ASSERT(compareDates(game->date,DATEMIN)); ASSERT(compareDates(game->date,DATEMAX));
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


    printf("|%3d - %-3u|", game->homePoints, game->awayPoints);

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
    if(ClearScreen)
        clearScreen();
    printf("___________________________________________________________________________________________\n"
           "| id |        Equipa da Casa        |  Resu.  |       Equipa Visitante       |    Data    |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^|\n");
    /* ex:  |1   |           FC Porto           |xxx - yyy|           SL Bosta           |  3/ 4/1994 |\n); */
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
    printf("-------------------------------------------------------------------------------------------\n");
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
    if(ClearScreen)
        clearScreen();
    /*               30 characters                   30 characters      Right aligned */
    printf("_____________________________________________________________________________\n"
           "| id |            Nome              |          Localidade          | Pontos |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    for (i=0; i < NUM_TEAMS; i++) {
        TablePrintTeam(i, &Teams[i]);
    }

    printf("------------------------------------------------------------------------------\n");
}

void NewGame(void) {
    Game game;
    size_t read;
    char str[NAME_SIZE];
    list_t* tmp;
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

    printf("Resultado (pts-pts)? "); fflush(stdout);
    read = readString(str, NAME_SIZE);
    if (!strToResult(str, &game.homePoints, &game.awayPoints))
        return ;

    printf("Jogo adicionado!\n");

    tmp=GameListAddGame(Games, game, true);
}
void DeleteGame(char* input) {
    list_t* iter;
    Game* g;
    size_t i=0;
    int id;
    ASSERT(input);
    if (!*input) {
        char line[100];
        ShowGames();
        printf("A tabela mais recente de jogos esta por cima desta frase.\n");
        printf("Deseja remover um destes jogos (s/n)? "); fflush(stdout);
        if(!readString(line, 100)) {
            goto err;
        }
        if (strCaseEqual(line, "s")) {
            ;
        } else if (strCaseEqual(line, "n")) {
            printf("Deseja ver a lista geral de jogos ou a de uma equipa em particular? (geral/particular) "); fflush(stdout);
            if(!readString(line, 100)) {
                goto err;
            }
            if (strCaseEqual(line, "geral")) {
                LastGameList = NULL;
                ShowGames();
            } else if (strCaseEqual(line, "particular")) {
                Team* team;
                printf("Qual a equipa cujos jogos quer ver? (nome/id) "); fflush(stdout);
                if(!readString(line, 100)) {
                    goto err;
                }
                team = getTeamFromInput(line);
                if(!team) {
                    goto err;
                }
                TeamUpdateGameListCache(team, NULL);
                LastGameList = team->gameList;
                ShowGames();
            } else {
                goto err;
            }
        } else {
            goto err;
        }

        printf("Insira o ID do jogo: "); fflush(stdout);

        if(!readString(input, 10)) {
            goto err;
        }
    }

    trimString(input);
    id = atoi(input);
    if (id < 0)
        goto err;
    if (LastGameList == NULL) {
        iter = Games->next;
        while (!ListIsFooter(iter)) {
            if (i++==(size_t)id)
                break;
            iter = ListIterateNext(iter);
        }

        if(ListIsFooter(iter))
            goto err;

        g = GAMELIST_GAME(iter);
        ASSERT(g->homeTeam);
        ASSERT(g->awayTeam);
        TeamDelGame(g->homeTeam, g);
        TeamDelGame(g->awayTeam, g);
        if (ScoreboardList)
            ScoreboardListUpdate(ScoreboardList, g);
        ListDel(iter); /* This effectively DELETES the game from memory */
        UpdateGames();
    } else {
        list_t* tmp;
        iter = LastGameList->next;
        while (!ListIsFooter(iter)) {
            if (i++==(size_t)id)
                break;
            iter = ListIterateNext(iter);
        }
        if(ListIsFooter(iter))
            goto err;
        tmp = (list_t*)iter->data;
        g = GAMELIST_GAME(tmp);
        ASSERT(g->homeTeam);
        ASSERT(g->awayTeam);
        TeamDelGame(g->homeTeam, g);
        TeamDelGame(g->awayTeam, g);
        if (ScoreboardList)
            ScoreboardListUpdate(ScoreboardList, g);
        ListDel(tmp); /* The cool thing here is that tmp is already the ponter to the node!! */
    }

    printf("Jogo eliminado.\n");
    return;
    err:
    printf("Resposta invalida.\n");
    return ;
}
void ShowScoreboard(void) {
    list_t* tmp;
    int i=1;
    if(ClearScreen)
        clearScreen();
    ScoreboardList = ScoreboardListUpdate(ScoreboardList, NULL);
    tmp = ScoreboardList->next; /* Jump over header. FIXME: Need function for this */

    printf("_____________________________________________________________________________\n"
           "|Pos.|            Nome              |          Localidade          | Pontos |\n"
           "|^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    while (!ListIsFooter(tmp)) {
        TablePrintTeam(i++, (Team*)tmp->data);
        tmp = ListIterateNext(tmp);
    }
    printf("-----------------------------------------------------------------------------\n");
}
