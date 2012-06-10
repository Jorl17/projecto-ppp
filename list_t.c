#include <stdlib.h> /* NULL, free(), malloc() */
#include <assert.h>
#define ASSERT assert
#include "list_t.h"

list_t* ListNew(void) {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    if ( list ) {
        list->data = NULL;
        list->next = NULL;
        list->prev = NULL;
    }

    list->next = (list_t*)malloc(sizeof(list_t));

    if (list->next) {
        list->next->data = NULL;
        list->next->prev = list;
        list->next->next = NULL;
    }

    return list;
}

void ListDelete(list_t* list) {
    list_t* tmp;
    ASSERT(list);
    while ( list->next ) {
        tmp = list;
        list = list->next;
        free(tmp->data);
        free(tmp);
    }
    free(list);
}

/*
  Find the first element whose data is "greater than or equal to that" of Key.
  We return that element or the footer, meaning that the returned element
  is the element that should go after a new element (to keep the order).

  key is a pointer, as obvious, and funct should receive two pointers to compare
  them and return -1, 0 or 1 (following strcmp conventions).
 */
list_t* ListSearch(list_t* list, void* key, compareFunc funct) {
    int compareOutcome;
    ASSERT(list); ASSERT(key);

    list = list->next; /* Go over the header */

    while ( list->next ) { /* While we haven't reached the footer */

        compareOutcome = /*compareDates(list->game.date, key->date) ;*/
                         funct(list->data, key);

        /* If we finally find an element whose data is bigger than ours or equal,
          then, to keep order, we must be inserted right before it. Our search
          has ended */
        if (compareOutcome >= 0) {
            break;
        }

        list = list->next;

    }
    return list;
}

void ListDel(list_t* l) {
    ASSERT(l);
    l->prev->next = l->next;
    l->next->prev = l->prev;
    free(l->data);
    free(l);

}

list_t* ListIterateNext(list_t* list) {
    ASSERT(list);
    return list->next;
}


list_t* ListAdd(list_t* list, void* g, compareFunc funct) {
    list_t* node;
    list_t* nodeToBeAfterNew;
    ASSERT(list);

    node = (list_t*) malloc(sizeof(list_t));
    if ( !node ) {
        /* FIXME: No more memory -- do something? */
        return NULL;
    }

    nodeToBeAfterNew = ListSearch(list, g, funct);
    node->data = g;
    node->next = nodeToBeAfterNew;
    nodeToBeAfterNew->prev->next = node;
    node->prev = nodeToBeAfterNew->prev;
    nodeToBeAfterNew->prev = node;

    return node;

}

/*
  Gets the next element in the list.
 */
list_t* ListIteratePrev(list_t* list) {
    ASSERT(list);
    return list->prev;
}

bool ListIsHeader(list_t* list) {
    return list->prev==NULL;
}

bool ListIsFooter(list_t* list) {
    return list->next == NULL;
}
