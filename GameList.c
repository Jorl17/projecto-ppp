#include "datatypes.h"
#include <stdlib.h> /* malloc(), free() */

/*
  Create a new list -- simply create the header.
 */
GameList* GameListNew(void) {
    GameList* list = malloc(sizeof(GameList*));
    if ( list ) {
        list->game = nullGame;
        list->next = NULL;
    }

    return list;
}

/*
  Delete a list.
 */
void GameListDelete(GameList* list) {
    GameList* tmp;
    while ( list->next ) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    free(list);
}


GameList* GameListAddGame(GameList* l, Game g) {

}
