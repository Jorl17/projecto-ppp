#include <stdio.h>    /* printf() */
#include <string.h>   /* strcmp() */
#include <assert.h>
#include "string.h" /* isStrNumber(),readString() */
#include "datatypes.h"
#include "Team.h"
#include "TeamGameList.h"
#include "GameList.h"
#include "Date.h"
#include "ScoreBoardList.h"
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
    trimString(input);
    if ( isStrNumber(input) ) {
        size_t i = (size_t)atoi(input);
        if (i < NUM_TEAMS)
            return &Teams[i];
    }
    /* input must have the team name.*/
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

void TablePrintTeam(size_t i, bool showPos, Team* t) {
    size_t j, len;
    if (showPos) {
      printf("|%-9lu", i);
    }
  
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
    printf("________________________________________________________________________\n"
           "|            Nome              |          Localidade          | Pontos |\n"
           "|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    for (i=0; i < NUM_TEAMS; i++) {
        TablePrintTeam(i, false, &Teams[i]);
    }

    printf("-------------------------------------------------------------------------\n");
}

void TeamNameError(char str[]) {
  printf("%s não é uma equipa registada no campeonato.\n\n", str);
}

void RequestPoints(char msg[], uint8_t* points) {
  char str[NAME_SIZE];
  size_t read;
  int pts;
  
  Points:
  printf("%s", msg); fflush(stdout);
  read = readString(str, NAME_SIZE);
  if (!read) {
    printf("O valor tem de ser um número (limite de 255 pontos).\n\n");
    goto Points;
  }
  
  if (!isStrNumber(str) || (pts = atoi(str))>255 ) { /* ANSI C ensures us that the conditions will be evaluated in this order */
    printf("O valor tem de ser um número (limtie de 255 pontos).\n\n");
    goto Points;
  }
  
  *points = pts;
}

void NewGame(void) {
    size_t read;
    char str[NAME_SIZE];
  
    Game game;
    list_t* tmp;

    Home_team:
    printf("Equipa da Casa: "); fflush(stdout);
    read = readString(str, NAME_SIZE);
    if (!read)
        goto Home_team;

    else if ( ! (game.homeTeam = getTeamFromInput(str)) ) {
      TeamNameError(str);
      goto Home_team;
    }

    Away_team:
    printf("Equipa Visitante: "); fflush(stdout);
    read = readString(str, NAME_SIZE);
    if (!read)
        goto Away_team;

    else if ( ! (game.awayTeam = getTeamFromInput(str)) ) {
      TeamNameError(str);
      goto Away_team;
    }

    if (game.awayTeam==game.homeTeam) {
      printf("A equipa da casa e a visitante não podem ser a mesma.\n\n");
      goto Away_team;
    }
  
    Date:
    game.date=getDateFromUser("Data: ");
    if (!compareDates(game.date,DATEMIN)) {
      printf("A data não é válida. O formato é: d/m/yyyy.\n\n");
      goto Date;
    }

    RequestPoints("Pontos da casa: ",  &game.homePoints);
    RequestPoints("Pontos dos visitantes: ",  &game.awayPoints);
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
        printf("Deseja remover algum destes jogos (s/n)? "); fflush(stdout);
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
                printf("Qual a equipa cujos jogos quer ver? "); fflush(stdout);
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

        printf("Insira o identificador do jogo: "); fflush(stdout);

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
        WriteGames();
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

    printf("__________________________________________________________________________________\n"
           "| Posição |            Nome              |          Localidade          | Pontos |\n"
           "|^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|^^^^^^^^|\n");
    while (!ListIsFooter(tmp)) {
        TablePrintTeam(i++, true, (Team*)tmp->data);
        tmp = ListIterateNext(tmp);
    }
    printf("----------------------------------------------------------------------------------\n");
}
