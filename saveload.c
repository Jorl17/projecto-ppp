#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Team.h"
#include "GameList.h"
#include "saveload.h"
#include "string.h"

#define ERROR_OUT(msg, ...) do {printf("ERROR: " msg "\n" , __VA_ARGS__); fclose(file); exit(-1);} while(0)

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
    if (!file)
        ERROR_OUT("Erro ao abrir o ficheiro das equipas.%s","\n");
    NUM_TEAMS = 0;

    while (readStringFile(line, 100, file)) {
        count++;
        if (!strCaseEqualn(line, "Nome:", 5))
            ERROR_OUT("Erro ao encontrar o nome da equipa na linha %lu. Lido: '%s'", count, line);

        trimString(&line[5]);
        if (strlen(&line[5]) >= NAME_SIZE-1)
                    ERROR_OUT("Nome de equipa demasiado longo na linha %lu. Lido: '%s'", count, line);

        strcpy(name, &line[5]);


        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se uma localidade). na linha %lu", count);
        count++;

        if (!strCaseEqualn(line, "Localidade:",11))
            ERROR_OUT("Erro ao encontrar a localidade da equipa na linha %lu. Lido: '%s'", count, line);

        trimString(&line[11]);
        if (strlen(&line[11]) >= NAME_SIZE-1)
            ERROR_OUT("Localidade de equipa demasiado longa na linha %lu. Lido; '%s'", count, line);

        strcpy(location, &line[11]);
        trimString(location);

        InsertTeamOrdered(name, location);

        while((r=fgetc(file))=='\n') count++;
        ungetc(r, file);
    }
    fclose(file);
}

void ReadGames() {
    char line[100];
    int r;
    size_t count=0;
    FILE *file = fopen ("games.txt", "r");
    if (!file)
        ERROR_OUT("Erro ao abrir o ficheiro dos jogos.%s","\n");
    Game tmp;
    Games = ListNew();
    while (readStringFile(line, 100, file)) {
        count++;
        if (!strCaseEqualn(line, "Casa:", 5))
            ERROR_OUT("Erro ao encontrar o nome da equipa da casa na linha %lu. Lido: '%s'", count, line);

        trimString(&line[5]);
        if (strlen(&line[5]) >= NAME_SIZE-1)
            ERROR_OUT("Nome de equipa demasiado longo na linha %lu. Lido: '%s'", count, line);

        tmp.homeTeam=TeamFind(&line[5]);
        if (!tmp.homeTeam)
            ERROR_OUT("Nome de equipa não encontrado (ou inválido) na linha %lu. Lido: '%s'", count, line);

        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se uma equipa). na linha %lu", count);
        count++;

        if (!strCaseEqualn(line, "Fora:",5))
            ERROR_OUT("Erro ao encontrar a localidade da equipa na linha %lu. Lido: '%s'", count, line);

        trimString(&line[5]);
        if (strlen(&line[5]) >= NAME_SIZE-1)
            ERROR_OUT("Nome de equipa demasiado longo na linha %lu. Lido: '%s'", count, line);

        tmp.awayTeam=TeamFind(&line[5]);
        if (!tmp.awayTeam)
            ERROR_OUT("Nome de equipa não encontrado (ou inválido) na linha %lu. Lido: '%s'", count, line);

        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se uma data). na linha %lu", count);
        count++;

        if (!strCaseEqualn(line, "Data:",5))
            ERROR_OUT("Erro ao encontrar o resultado da equipa na linha %lu. Lido: '%s'", count, line);

        trimString(&line[5]);
        tmp.date = getDateFromInput(&line[5]);
        if (!memcmp(&tmp.date,&DATEMIN, sizeof(Date)))
            ERROR_OUT("Erro ao interpretar a data na linha %lu. Lido: '%s'", count, line);

        if ((r=readStringFile(line, 100, file)) == 0)
            ERROR_OUT("Fim do ficheiro inesperado (esperava-se um resultado). na linha %lu", count);
        count++;

        if (!strCaseEqualn(line, "Resultado:",10))
            ERROR_OUT("Erro ao encontrar o resultado da equipa na linha %lu. Lido: '%s'", count, line);

        trimString(&line[10]);
        if (!strToResult(&line[10], &tmp.homePoints, &tmp.awayPoints))
            ERROR_OUT("Erro ao interpretar o resultado na linha %lu. Lido: '%s'", count, line);

        GameListAddGame(Games, tmp, false);

        while((r=fgetc(file))=='\n') count++;
        ungetc(r, file);
    }

    fclose(file);
}


// Write
void WriteGames(void) {
    FILE *file = fopen ("games.txt", "w");
    if (!file)
        ERROR_OUT("Erro ao abrir o ficheiro dos jogos.%s","\n");
    list_t* node = Games->next;

    while (node->next != NULL) {
        Game* game = GAMELIST_GAME(node);

        fprintf(file,"Casa:%s\nFora:%s\n",game->homeTeam->name, game->awayTeam->name);
        fprintf(file, "Data:%d/%d/%d\n", (int)game->date.day, (int)game->date.month, (int)game->date.year);
        fprintf(file,"Resultado:%d-%d\n\n", (int)game->homePoints, (int)game->awayPoints);

        node = node->next;
    }

    fclose(file);

}
