#include <genesis.h>
#include "entity.h"
#include "sprites.h"
#include "bullets.h"
#include "collision.h"
#include "const.h"

void Bullets_onCollide(Bullets *b, SimpleCollision *collision)
{
  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    if (e->collision == collision)
    {
      Entity_kill(e);
      b->onScreenNum--;
      break;
    }
    e++;
  }
}

Bullets *Bullets_init(const SpriteDefinition *bulletSprite, enum CollisionType collisionType, Collision_onCollide *onCollide)
{
  Bullets *b = (Bullets *)MEM_alloc(sizeof(Bullets));
  b->onScreenNum = 0;

  Entity *e = b->list;
  for (u16 i = 0; i < MAX_BULLETS; i++)
  {
    e->x = 0;
    e->y = -10;
    e->w = 8;
    e->h = 8;
    e->velx = 0;
    e->vely = 0;
    e->sprite = SPR_addSprite(bulletSprite, 0, -10, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    e->collision = Collision_create(collisionType, FALSE, 0, -10, 4, 4, e);
    e->collision->onCollide = onCollide;

    Entity_kill(e);
    e++;
  }
  return b;
}

void Bullets_shoot(Bullets *b, int fromX, int fromY, int velx, int vely)
{
  if (b->onScreenNum >= MAX_BULLETS)
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

      Entity_revive(e);

      SPR_setPosition(e->sprite, e->x, e->y);
      b->onScreenNum++;
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
        b->onScreenNum--;
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