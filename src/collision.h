#pragma once

#include <genesis.h>
#include "entity.h"
#include "doubly_linked_list.h"

typedef struct _entity Entity;
typedef struct _simpleCollision SimpleCollision;

enum CollisionType
{
  COLLISION_PLAYER,
  COLLISION_PLAYER_BULLET,
  COLLISION_ENEMY,
  COLLISION_ENEMY_BULLET,
  COLLISION_TYPE_MAX,
};

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
  Entity *entity;
  Collision_onCollide *onCollide;
} SimpleCollision;

SimpleCollision *Collision_create(enum CollisionType type, bool enabled, s16 x, s16 y, u16 w, u16 h, Entity *entity);

void Collision_update();

void Collision_destroy(SimpleCollision *e);