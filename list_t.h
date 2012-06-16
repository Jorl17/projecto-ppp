#ifndef LIST_T_H
#define LIST_T_H 1
#include "fixsizedtypes.h"
typedef struct _list_t {
    void* data;
    struct _list_t* next;
    struct _list_t* prev;
} list_t;

/* This defines a type compareFunc which is the type of a pointer to a compare
  function. It follows strcmp conventions and accepts two pointers to keys.
  */
typedef int (*compareFunc)(void*, void*);

list_t* ListNew(void);
void ListDelete(list_t* list);

/*
  Find the first element whose data is "greater than or equal to that" of Key.
  We return that element or the footer, meaning that the returned element
  is the element that should go after a new element (to keep the order).

  key is a pointer, as obvious, and funct should receive two pointers to compare
  them and return -1, 0 or 1 (following strcmp conventions).
 */
list_t* ListSearch(list_t* list, void* key, compareFunc funct);

void ListDel(list_t* l);

list_t* ListIterateNext(list_t* list);
/*
  Gets the next element in the list.
 */
list_t* ListIteratePrev(list_t* list);

bool ListIsHeader(list_t* list);

bool ListIsFooter(list_t* list);

list_t* ListAdd(list_t* list, void* g, compareFunc funct);

list_t* ListFindNode(list_t* list, void* data);

#define LIST_DATA(list, type) ((type*)list->data)
#endif /* LIST_T_H */
