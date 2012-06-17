#include "TeamGameList.h"
#include "GameList.h" /* compareDatesAux() */
#include <assert.h>
#define ASSERT assert

int compareDatesFromNodeAux(void* d1, void* d2) {
    return compareDatesAux(((Game*)((list_t*)d1)->data),
                           ((Game*)((list_t*)d2)->data));
}

int compareGamesAux(list_t* d1, Game* g) {
    return (GAMELIST_GAME(d1) == g);
}

list_t* TeamGameListAdd(list_t* list, list_t* g) {
    return ListAdd(list, (void*)g, &compareDatesFromNodeAux);
}

list_t* TeamGameListAppend(list_t* list, list_t* g) {
    list_t* newNode = (list_t*)malloc(sizeof(list_t));
    while (!ListIsFooter(list->next)) list = ListIterateNext(list);

    newNode->data = (void*)g;
    newNode->next = list->next;
    newNode->prev = list;
    list->next = newNode;
    newNode->next->prev = newNode;

    return newNode;
}

////
// This function is specific because list_t does not actually create content.
//
void TeamGameListDel(list_t* l) {
    ASSERT(l);
    l->prev->next = l->next;
    l->next->prev = l->prev;
    free(l);
}

////
// Alias for the above, but uses a game (hence, has to find the node that has it)
//
void TeamGameListDelGame(list_t* list, Game* g) {
    ASSERT(list);
    ASSERT(g);

    list = list->next;
    while(!ListIsFooter(list)) {
        if (compareGamesAux(list->data, g)) {
            TeamGameListDel(list);
            break;
        }

        list = ListIterateNext(list);
    }

}
