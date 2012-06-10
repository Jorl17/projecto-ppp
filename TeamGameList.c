#include "TeamGameList.h"
#include "GameList.h" /* compareDatesAux() */
#include <assert.h>
#define ASSERT assert

int compareDatesFromNodeAux(void* d1, void* d2) {
    return compareDatesAux(((Game*)((list_t*)d1)->data),
                           ((Game*)((list_t*)d2)->data));
}

list_t* TeamGameListAdd(list_t* list, list_t* g) {
    return ListAdd(list, (void*)g, &compareDatesFromNodeAux);
}

/****
** This function is specific because list_t does not actually create content.
** FIXME: NOT USED YET!!!
*/
void TeamGameListDel(list_t* l) {
    ASSERT(l);
    l->prev->next = l->next;
    l->next->prev = l->prev;
    free(l);
}
