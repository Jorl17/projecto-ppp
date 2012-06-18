#include "datatypes.h" /* Team*, Game* (forward declared) */
extern bool ClearScreen;

void clearScreen(void);
Team* getTeamFromInput(char* input);
void printGame(size_t id, Game* game);
void ShowGames(void);
void ListTeams(void);
void NewGame(void);
void DeleteGame(char*);
void ShowScoreboard(void);
