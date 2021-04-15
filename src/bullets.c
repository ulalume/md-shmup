#include <genesis.h>
#include "sprites.h"
#include "bullets.h"
#include "entity.h"
#include "collision.h"

#define RIGHT_EDGE 320
#define BOTTOM_EDGE 224

void Bullets_onCollide(Bullets *b, SimpleCollision *collision)
{
  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    if (e->collision == collision)
    {
      Entity_kill(e);
      b->onScreen--;
      break;
    }
    e++;
  }
}

Bullets *Bullets_create()
{
  Bullets *b = (Bullets *)MEM_alloc(sizeof(Bullets));
  b->onScreen = 0;

  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    e->x = 0;
    e->y = -10;
    e->w = 8;
    e->h = 8;
    e->velx = 0;
    e->vely = 0;
    e->sprite = SPR_addSprite(&bullet_sprite, i * 10, 0, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    e->collision = Collision_create(COLLISION_PLAYER_BULLET, FALSE, 0, -10, 4, 4);
    Entity_kill(e);
    e++;
  }
  return b;
}

void Bullets_shoot(Bullets *b, int fromX, int fromY, int velx, int vely, enum CollisionType collisionType)
{
  if (b->onScreen >= MAX_BULLETS)
    return;

  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    if (e->health == 0)
    {
      e->x = fromX;
      e->y = fromY;
      e->velx = velx;
      e->vely = vely;
      e->collision->type = collisionType;

      Entity_revive(e);

      SPR_setPosition(e->sprite, e->x, e->y);
      b->onScreen++;
      break;
    }
    e++;
  }
}

void Bullets_update(Bullets *b)
{
  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    if (e->health > 0)
    {
      Entity_update(e);

      if (e->y + e->h < 0 || e->y > BOTTOM_EDGE ||
          e->x + e->w < 0 || e->x > RIGHT_EDGE)
      {
        Entity_kill(e);
        b->onScreen--;
      }
    }
    e++;
  }
}

void Bullets_destroy(Bullets *b)
{
  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    Entity_destroy(e);
    e++;
  }
  MEM_free(b);
}