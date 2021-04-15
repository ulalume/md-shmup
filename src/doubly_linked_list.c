
#include "doubly_linked_list.h"

void DLList_add(DLList *l, DLListNode *n)
{
  if (l->last == NULL)
  {
    l->first = n;
    l->last = n;
    return;
  }

  l->last->next = n;
  n->prev = l->last;
  l->last = n;
}

void DLList_remove(DLList *l, DLListNode *n)
{
  if (n->prev == NULL && n->next == NULL)
  {
    l->first = NULL;
    l->last = NULL;
    return;
  }

  if (n->prev == NULL)
  {
    l->first = n->next;
    n->next->prev = n->prev;
    return;
  }

  if (n->next == NULL)
  {
    l->last = n->prev;
    n->prev->next = n->next;
    return;
  }

  n->prev->next = n->next;
  n->next->prev = n->prev;
}
