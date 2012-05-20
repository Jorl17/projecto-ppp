#include <stdio.h>
#include <string.h>
#include "Team.h"
#include "GameList.h"
#include "saveload.h"


// Read
void ReadFiles() {
	NUM_TEAMS = 50; // I think this should be a #define contant, instead of the size_t wackamole

	ReadTeams();
	ReadGames();
};


void ReadTeams() {
	FILE *file = fopen ('WHERE_IS_THE_FILE_SAVED?', 'r');
	char line[NAME_SIZE * 2];
	int i = 0;
	
	while (fgets(line,1, sizeof(line), file) && i < NUM_TEAMS) {
		strcpy(Teams[i].name, line);
		strcpy(Team[i].location, line + NAME_SIZE);
		i++;
	};
};

void ReadGames() {
	
};


// Write
void UpdateGames(int start) {
	
};