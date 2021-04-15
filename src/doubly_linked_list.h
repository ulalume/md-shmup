#pragma once

#include <genesis.h>
typedef struct _dllistnode DLListNode;

typedef struct _dllistnode
{
  DLListNode *prev;
  DLListNode *next;
} DLListNode;

typedef struct
{
  DLListNode *first;
  DLListNode *last;
} DLList;

void DLList_add(DLList *l, DLListNode *n);
void DLList_remove(DLList *l, DLListNode *n);