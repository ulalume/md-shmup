
#include <genesis.h>
#include "collision.h"
#include "entity.h"

#include "doubly_linked_list.h"

#define MAX_COLLISION (100)

SimpleCollision *Collision_create(enum CollisionType type, bool enabled, s16 x, s16 y, u16 w, u16 h, Entity *entity);
static bool Collision_collide(SimpleCollision *a, SimpleCollision *b);
void Collision_destroy(SimpleCollision *c);
void Collision_update();

static DLList collisionDLList;

const bool COLLISION_TABLE[COLLISION_TYPE_MAX][COLLISION_TYPE_MAX] = {
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
};

SimpleCollision *Collision_create(enum CollisionType type, bool enabled, s16 x, s16 y, u16 w, u16 h, Entity *entity)
{
  SimpleCollision *c = (SimpleCollision *)MEM_alloc(sizeof(SimpleCollision));
  c->type = type;
  c->enabled = enabled;
  c->x = x;
  c->y = y;
  c->w = w;
  c->h = h;
  c->entity = entity;

  DLList_add(&collisionDLList, (DLListNode *)c);
  return c;
}

static bool Collision_collide(SimpleCollision *a, SimpleCollision *b)
{
  return a->enabled && b->enabled && COLLISION_TABLE[a->type][b->type] && a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h >= b->y;
}

void Collision_destroy(SimpleCollision *c)
{
  DLList_remove(&collisionDLList, (DLListNode *)c);
  MEM_free(c);
}
void Collision_update()
{
  // TODO: 途中で collision を削除されたら多分おかしくなる
  DLListNode *c = collisionDLList.first;
  while (c != NULL)
  {
    DLListNode *c2 = c->next;
    while (c2 != NULL)
    {
      SimpleCollision *col = (SimpleCollision *)c;
      SimpleCollision *col2 = (SimpleCollision *)c2;
      if (Collision_collide(col, col2))
      {
        if (col->onCollide != NULL)
          col->onCollide(col, col2);
        if (col2->onCollide != NULL)
          col2->onCollide(col2, col);
      }

      c2 = c2->next;
    }
    c = c->next;
  }
}