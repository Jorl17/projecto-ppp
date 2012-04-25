#include <stdlib.h> /* malloc(), free() */
#include <assert.h>
#include "GameList.h"
#include "datatypes.h"
#include "Date.h"   /* compareDates() */
#define ASSERT assert
/*
  Create a new list -- simply create the header.
 */
GameList* GameListNew(void) {
    GameList* list = (GameList*)malloc(sizeof(GameList));
    if ( list ) {
        list->game = nullGame;
        list->next = NULL;
        list->prev = NULL;
    }

    return list;
}

void GameListDelete(GameList* list) {
    GameList* tmp;
    ASSERT(list);
    while ( list->next ) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    free(list);
}

/*
  Find the first element whose date is greater than or equal to that of Key.
  In the end, *curr will have that element and *prev the element right before it.
  In case such an element isn't found, *curr will have the header.

 */
void GameListSearch(GameList* list, const Game* key, GameList** curr, GameList** prev) {
    int compareOutcome;
    ASSERT(list); ASSERT(key); ASSERT(curr); ASSERT(prev); ASSERT(*curr); ASSERT(*prev);

    *prev = list; *curr = list->next; /* *prev is pointing to the header now */;
    while ( true ) {

        if (!(*curr))
            break; /* Not found */
        compareOutcome = compareDates((*curr)->game.date, key->date) <0;

        if (compareOutcome >= 0) {
            break; /* Found the same date or a bigger date */
        }

        *prev = list;
        *curr = (*curr)->next;
    }

}

void GameListAddGame(GameList* list, Game g) {
    GameList* nodeToGoBefore;
    GameList* nodeToGoAfter;
    GameList* node;
    ASSERT(list);

    GameListSearch(list, &g, &nodeToGoBefore, &nodeToGoAfter);

    node = (GameList*) malloc(sizeof(GameList));
    if ( !node ) {
        /* FIXME: No more memory -- do something? */
        return ;
    }

    nodeToGoBefore->prev = node;
    node->next = nodeToGoBefore;
    nodeToGoAfter->next = node;
    node->prev = nodeToGoAfter;
}

void GameListDelGame(GameList* list) {
    GameList* prev = list->prev;
    ASSERT(list);
    prev->next = list->next;
    list->prev = prev;
    free(list);
}
