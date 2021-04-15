#pragma once

#include <genesis.h>
#include "entity.h"

#define MAX_BULLETS 6

typedef struct
{
  int onScreen;
  Entity list[MAX_BULLETS];
} Bullets;

Bullets *Bullets_init();
void Bullets_shoot(Bullets *b, int fromX, int fromY, int velx, int vely, enum CollisionType collisionType);
void Bullets_update(Bullets *b);
void Bullets_destroy(Bullets *b);

void Bullets_onCollide(Bullets *b, SimpleCollision *collision);
