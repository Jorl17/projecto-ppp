#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Team.h"
#include "GameList.h"
#include "saveload.h"
#include "string.h"

#define ERROR_OUT(msg, ...) {printf("ERROR: " msg "\n" , ## __VA_ARGS__); exit(-1);}

// Read
void ReadFiles() {
	ReadTeams();
	ReadGames();
};


static void InsertTeamOrdered(char* name, char* location) {
    size_t i;
    Teams = realloc(Teams, sizeof(Team) * (NUM_TEAMS+1));
    for (i=0; i < NUM_TEAMS; i++) {
        if (strcmp(Teams[i].name, name)>=0) {
            //at i-1
            memmove(&Teams[i+1], &Teams[i], sizeof(Team)*(NUM_TEAMS-i));
            break;
        }
    }

    Teams[i].points = -1;
    Teams[i].gameList = NULL;
    strcpy(Teams[i].name, name);
    strcpy(Teams[i].location, location);
    NUM_TEAMS++;
}

void ReadTeams() {
    char line[100];
    char name[NAME_SIZE], location[NAME_SIZE];
    int r;
    size_t count=0;
    FILE *file = fopen ("teams.txt", "r");

    NUM_TEAMS = 0;

    while (readStringFile(line, 100, file)) {
        count++;
        if (!strCaseEqual(line, "Nome:", 5))
            ERROR_OUT("Erro ao encontrar o nome da equipa na linha %lu. Lido: '%s'", count, line)

        trimString(&line[5]);
        if (strlen(&line[5]) >= NAME_SIZE-1)
                    ERROR_OUT("Nome de equipa demasiado longo na linha %lu. Lido: '%s'", count, line)

        strcpy(name, &line[5]);


        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se uma localidade).")
        count++;

        if (!strCaseEqual(line, "Localidade:",11))
            ERROR_OUT("Erro ao encontrar a localidade da equipa na linha %lu. Lido: '%s'", count, line)

        trimString(&line[11]);
        if (strlen(&line[11]) >= NAME_SIZE-1)
            ERROR_OUT("Localidade de equipa demasiado longa na linha %lu. Lido; '%s'", count, line)

        strcpy(location, &line[11]);
        trimString(location);

        InsertTeamOrdered(name, location);

        while((r=fgetc(file))=='\n') count++;
        ungetc(r, file);
    }
}

void ReadGames() {
    char line[100];
    char name[NAME_SIZE], location[NAME_SIZE];
    int r;
    size_t count=0;
    FILE *file = fopen ("games.txt", "r");
    Game tmp;
    Games = ListNew();
    while (readStringFile(line, 100, file)) {
        count++;
        if (!strCaseEqual(line, "Casa:", 5))
            ERROR_OUT("Erro ao encontrar o nome da equipa da casa na linha %lu. Lido: '%s'", count, line)

        trimString(&line[5]);
        if (strlen(&line[5]) >= NAME_SIZE-1)
            ERROR_OUT("Nome de equipa demasiado longo na linha %lu. Lido: '%s'", count, line)

        tmp.homeTeam=TeamFind(&line[5]);
        if (!tmp.homeTeam)
            ERROR_OUT("Nome de equipa não encontrado (ou inválido) na linha %lu. Lido: '%s'", count, line)

        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se uma equipa).")
        count++;

        if (!strCaseEqual(line, "Fora:",5))
            ERROR_OUT("Erro ao encontrar a localidade da equipa na linha %lu. Lido: '%s'", count, line)

        trimString(&line[5]);
        if (strlen(&line[5]) >= NAME_SIZE-1)
            ERROR_OUT("Nome de equipa demasiado longo na linha %lu. Lido: '%s'", count, line)

        tmp.awayTeam=TeamFind(&line[5]);
        if (!tmp.awayTeam)
            ERROR_OUT("Nome de equipa não encontrado (ou inválido) na linha %lu. Lido: '%s'", count, line)

        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se uma data).")
        count++;

        if (!strCaseEqual(line, "Data:",5))
            ERROR_OUT("Erro ao encontrar o resultado da equipa na linha %lu. Lido: '%s'", count, line)

        trimString(&line[5]);
        tmp.date = getDateFromInput(&line[5]);
        if (!memcmp(&tmp.date,&DATEMIN, sizeof(Date)))
            ERROR_OUT("Erro ao interpretar a data na linha %lu. Lido: '%s'", count, line)

        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se um resultado).")
        count++;

        if (!strCaseEqual(line, "Resultado:",10))
            ERROR_OUT("Erro ao encontrar o resultado da equipa na linha %lu. Lido: '%s'", count, line)

        trimString(&line[10]);
        if (!strToResult(&line[10], &tmp.homePoints, &tmp.awayPoints))
            ERROR_OUT("Erro ao interpretar o resultado na linha %lu. Lido: '%s'", count, line)

        GameListAddGame(Games, tmp);

        while((r=fgetc(file))=='\n') count++;
        ungetc(r, file);
    }
}


// Write
void UpdateGames(int start) {
    FILE *file = fopen ("games.txt", "r+");
    list_t* node = Games;

    int numLines = start * 5;
    while (numLines > 0) {
        int c = fgetc(file);

        if (c == '\n') {
            numLines--;
        } else if (c == EOF) {
            printf("Error, not enough games found on games.txt. The file may have been corrupted.");
            return;
        }
    }

    while (start > 0) {
        node = node->next;
        start--;
    }

    while (node != NULL) {
        Game* game = GAMELIST_GAME(node);

        fprintf(file, "%d/%d/%d\n", (int)game->date.day, (int)game->date.month, (int)game->date.year);
        /*fprintf(file, "%d\n\n", game->outcome);*/

        node = node->next;
    }
}

