#pragma once

#include <genesis.h>
#include "doubly_linked_list.h"

enum CollisionType
{
  COLLISION_PLAYER,
  COLLISION_PLAYER_BULLET,
  COLLISION_ENEMY,
  COLLISION_ENEMY_BULLET,
  COLLISION_TYPE_MAX,
};

typedef struct _simpleCollision SimpleCollision;

extern const bool COLLISION_TABLE[COLLISION_TYPE_MAX][COLLISION_TYPE_MAX];
typedef void Collision_onCollide(SimpleCollision *me, SimpleCollision *target);

typedef struct _simpleCollision
{
  DLListNode _node;
  enum CollisionType type;
  bool enabled;
  s16 x;
  s16 y;
  u16 w;
  u16 h;
  Collision_onCollide *onCollide;
} SimpleCollision;

SimpleCollision *Collision_create(enum CollisionType type, bool enabled, s16 x, s16 y, u16 w, u16 h);

void Collision_update();

void Collision_destroy(SimpleCollision *e);