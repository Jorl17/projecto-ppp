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
  char line[NAME_SIZE * 2 + 2];
  
  Teams = malloc(sizeof(Team));
  NUM_TEAMS = 0;
  
	while (fgets(line, sizeof(line), file)) {
    realloc(Teams, sizeof(Team) * NUM_TEAMS);
		NUM_TEAMS++;
    
		strcpy(Teams[NUM_TEAMS].name, line);
		strcpy(Teams[NUM_TEAMS].location, line + NAME_SIZE + 1);
	};
  
  
};

void ReadGames() {
	
};


// Write
void UpdateGames(int start) {
	
};