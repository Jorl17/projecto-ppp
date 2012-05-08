#include <stdlib.h>     /* malloc(), free() */
#include <assert.h>
#include "datatypes.h"
#include "GameList.h"
#include "Date.h"       /* compareDates() */
#define ASSERT assert

/*
  Create a new list -- simply create the header and the footer.
 */

GameList* GameListNew(void) {
    GameList* list = (GameList*)malloc(sizeof(GameList));
    if ( list ) {
        list->game = NULL_GAME;
        list->game.date = DATEMIN;
        list->next = NULL;
        list->prev = NULL;
    }

    list->next = (GameList*)malloc(sizeof(GameList));

    if (list->next) {
        list->next->game = NULL_GAME;
        list->next->game.date = DATEMAX;
        list->next->prev = list;
        list->next->next = NULL;
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
  We return that element or the footer, meaning that the returned element
  is the element that should go after a new element (to keep the order).

 */
static GameList* GameListSearch(GameList* list, const Game* key) {
    int compareOutcome;
    ASSERT(list); ASSERT(key);

    list = list->next; /* Go over the header */

    while ( list->next ) { /* While we haven't reached the footer */

        compareOutcome = compareDates(list->game.date, key->date) ;

        /* If we finally find an element whose date is bigger than ours or equal,
          then, to keep order, we must be inserted right before it. Our seearch
          has ended */
        if (compareOutcome >= 0) {
            break;
        }

        list = list->next;

    }
    return list;
}

GameList* GameListAddGame(GameList* list, Game g) {
    GameList* node;
    GameList* nodeToBeAfterNew;
    ASSERT(list);

    node = (GameList*) malloc(sizeof(GameList));
    if ( !node ) {
        /* FIXME: No more memory -- do something? */
        return ;
    }

    nodeToBeAfterNew = GameListSearch(list, &g);
    node->game = g;
    node->next = nodeToBeAfterNew;
    nodeToBeAfterNew->prev->next = node;
    node->prev = nodeToBeAfterNew->prev;
    nodeToBeAfterNew->prev = node;

    return node;

}

void GameListDelGame(GameList* game) {
    ASSERT(game);
    game->prev->next = game->next;
    game->next->prev = game->prev;
    free(game);

}

GameList* GameListIterateNext(GameList* list) {
    ASSERT(list);
    return list->next;
}

/*
  Gets the next element in the list.
 */
GameList* GameListIteratePrev(GameList* list) {
    ASSERT(list);
    return list->prev;
}

bool GameListIsHeader(GameList* list) {
    return list->prev==NULL;
}

bool GameListIsFooter(GameList* list) {
    return list->next == NULL;
}
