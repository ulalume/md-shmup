
#include <genesis.h>
#include "collision.h"

#define MAX_COLLISION (100)

static void Collision_add(SimpleCollision *c);
SimpleCollision *Collision_create(enum CollisionType type, bool enabled, s16 x, s16 y, u16 w, u16 h);
static bool Collision_collide(SimpleCollision *a, SimpleCollision *b);
void Collision_destroy(SimpleCollision *c);
static void Collision_add(SimpleCollision *c);
static void Collision_remove(SimpleCollision *c);
void Collision_update();

static SimpleCollision *collisionFirst;
static SimpleCollision *collisionLast;

const bool COLLISION_TABLE[COLLISION_TYPE_MAX][COLLISION_TYPE_MAX] = {
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
};

static bool Collision_collide(SimpleCollision *a, SimpleCollision *b)
{
  return a->enabled && b->enabled && COLLISION_TABLE[a->type][b->type] && a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h >= b->y;
}
static void Collision_add(SimpleCollision *c)
{
  if (collisionLast == NULL)
  {
    collisionFirst = c;
    collisionLast = c;
    return;
  }

  collisionLast->next = c;
  c->prev = collisionLast;
  collisionLast = c;
}
static void Collision_remove(SimpleCollision *c)
{
  if (c->prev == NULL)
  {
    collisionFirst = c->next;
    c->next->prev = c->prev;
    return;
  }

  if (c->next == NULL)
  {
    collisionLast = c->prev;
    c->prev->next = c->next;
    return;
  }

  c->prev->next = c->next;
  c->next->prev = c->prev;
}

SimpleCollision *Collision_create(enum CollisionType type, bool enabled, s16 x, s16 y, u16 w, u16 h)
{
  SimpleCollision *c = (SimpleCollision *)MEM_alloc(sizeof(SimpleCollision));
  c->type = type;
  c->enabled = enabled;
  c->x = x;
  c->y = y;
  c->w = w;
  c->h = h;

  Collision_add(c);

  return c;
}

void Collision_destroy(SimpleCollision *c)
{
  Collision_remove(c);
  MEM_free(c);
}
void Collision_update()
{
  SimpleCollision *c = collisionFirst;
  while (c != NULL)
  {
    SimpleCollision *c2 = c->next;
    while (c2 != NULL)
    {
      if (Collision_collide(c, c2))
      {
        if (c->onCollide != NULL)
          c->onCollide(c, c2);
        if (c2->onCollide != NULL)
          c2->onCollide(c2, c);
      }

      c2 = c2->next;
    }
    c = c->next;
  }
}