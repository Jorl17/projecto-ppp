#include <stdio.h>
#include <string.h>
#include "Team.h"
#include "GameList.h"
#include "saveload.h"


// Read
void ReadFiles() {
	ReadTeams();
	ReadGames();
};


void ReadTeams() {
	FILE *file = fopen ("WHERE_IS_THE_FILE_SAVED?", "r");
  char line[NAME_SIZE * 2];
  
  Teams = malloc(sizeof(Team));
  NUM_TEAMS = 0;
  
  while (fgets(line, sizeof(line), file) != NULL) {
      NUM_TEAMS++;
      Teams = realloc(Teams, sizeof(Team) * NUM_TEAMS);

      strcpy(Teams[NUM_TEAMS].name, line);
      strcpy(Teams[NUM_TEAMS].location, line + NAME_SIZE + 1);
  };
};

void ReadGames() {
    FILE *file = fopen ("WHERE_IS_THE_FILE_SAVED?", "r");
    Games = malloc(sizeof(list_t));

    list_t* prev = NULL;
    int i = 0, v;

    while (fscanf(file, "%d", &v) != EOF) {
        i++;
        Games = realloc(Games, sizeof(list_t) * i);

        list_t* node = &Games[i];
        Game* game = GAMELIST_GAME(node);

        prev->next = node;
        node->prev = prev;
        game->homeTeam = &Teams[v];

        fscanf(file, "%d", &v);
        fscanf(file, "%d", &game->date.year);
        fscanf(file, "%d", &game->date.month);
        fscanf(file, "%d", &game->date.year);
        fscanf(file, "%d", &game->outcome);

        game->awayTeam = &Teams[v];
        prev = node;
    }
};


// Write
void UpdateGames(int start) {
	
};
