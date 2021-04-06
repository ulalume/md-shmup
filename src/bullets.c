#include <genesis.h>
#include "sprites.h"
#include "bullets.h"

#define RIGHT_EDGE 320
#define BOTTOM_EDGE 224

Bullets *Bullets_create()
{
  Bullets *b = (Bullets *)MEM_alloc(sizeof(Bullets));
  b->onScreen = 0;

  int i = 0;
  Entity *e = b->list;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    e->x = 0;
    e->y = -10;
    e->w = 8;
    e->h = 8;
    e->velx = 0;
    e->vely = 0;
    e->sprite = SPR_addSprite(&bullet_sprite, i * 10, 0, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    Entity_kill(e);
    e++;
  }
  return b;
}

void Bullets_shoot(Bullets *b, int fromX, int fromY, int velx, int vely)
{
  if (b->onScreen >= MAX_BULLETS)
    return;

  Entity *e = b->list;
  u16 i = 0;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    if (e->health == 0)
    {
      e->x = fromX;
      e->y = fromY;
      e->velx = velx;
      e->vely = vely;

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
  u16 i = 0;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    if (e->health > 0)
    {
      e->y += e->vely;
      e->x += e->velx;

      if (e->y + e->h < 0 || e->y > BOTTOM_EDGE ||
          e->x + e->x < 0 || e->x > RIGHT_EDGE)
      {
        Entity_kill(e);
        b->onScreen--;
      }
      else
      {
        SPR_setPosition(e->sprite, e->x, e->y);
      }
    }
    e++;
  }
}

void Bullets_destroy(Bullets *b)
{
  Entity *e = b->list;
  u16 i = 0;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    SPR_end(e->sprite);
    MEM_free(e);
    e++;
  }
  MEM_free(b);
}