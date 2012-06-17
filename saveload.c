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
	FILE *file = fopen ("/Users/Jaliborc/Documents/Disciplinas/PPP/Projecto/Projecto/teams.txt", "r");
  char name[NAME_SIZE];
  
  NUM_TEAMS = 0;
  Teams = NULL;
  
   while (fscanf(file, "Name: %s\n", &name) == 1) {
      Teams = realloc(Teams, sizeof(Team) * (NUM_TEAMS + 1));
      Teams[NUM_TEAMS].index = NUM_TEAMS;

      fscanf(file, "Location: %s\n\n", &Teams[NUM_TEAMS].location);
      strcpy(Teams[NUM_TEAMS].name, name);
     
      NUM_TEAMS++;
  };
};

void ReadGames() {
    FILE *file = fopen ("/Users/Jaliborc/Documents/Disciplinas/PPP/Projecto/games.txt", "r");
    int i = 0, v;
  
    Games = malloc(sizeof(list_t));
    list_t* prev = NULL;

    while (fscanf(file, "Home: %d\n", &v) == 1) {
        i++;
        Games = realloc(Games, sizeof(list_t) * i);

        list_t* node = &Games[i];
        Game* game = GAMELIST_GAME(node);

        prev->next = node;
        node->prev = prev;
        game->homeTeam = &Teams[v];
      
        int day, month, year;
        fscanf(file, "Away: %d\n", &v);
        fscanf(file, "%d/%d/%d\n", &day, &month, &year);
        fscanf(file, "%d\n\n", &game->outcome);
      
        game->date.day = day;
        game->date.month = month;
        game->date.year = year;
        game->awayTeam = &Teams[v];
        prev = node;
    }
  
    prev->next = NULL;
};


// Write
void WriteGames(int start) {
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
    
    fprintf(file, "Home: %d\n", game->homeTeam->index);
    fprintf(file, "Away: %d\n", game->awayTeam->index);
    fprintf(file, "%d/%d/%d\n", (int)game->date.day, (int)game->date.month, (int)game->date.year);
    fprintf(file, "%d\n\n", game->outcome);
    
    node = node->next;
  }
};
