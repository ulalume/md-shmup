#pragma once

#include <genesis.h>
#include "entity.h"
#include "collision.h"

#define MAX_BULLETS 6

typedef struct
{
  int onScreenNum;
  Entity list[MAX_BULLETS];
  Collision_onCollide *onCollide;
} Bullets;

Bullets *Bullets_init(const SpriteDefinition *bulletSprite, enum CollisionType collisionType, Collision_onCollide *onCollide);
void Bullets_shoot(Bullets *b, int fromX, int fromY, int velx, int vely);
void Bullets_update(Bullets *b);
void Bullets_destroy(Bullets *b);

void Bullets_onCollide(Bullets *b, SimpleCollision *collision);
