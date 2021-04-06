#ifndef _BULLETS_H_
#define _BULLETS_H_

#include <genesis.h>
#include "entity.h"

#define MAX_BULLETS 6

typedef struct
{
  int onScreen;
  Entity list[MAX_BULLETS];
} Bullets;

Bullets *Bullets_create();
void Bullets_shoot(Bullets *b, int fromX, int fromY, int velx, int vely);
void Bullets_update(Bullets *b);
void Bullets_destroy(Bullets *b);

#endif // _BULLETS_H_