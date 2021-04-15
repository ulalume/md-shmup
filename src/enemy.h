#pragma once

#include <genesis.h>
#include "entity.h"

enum EnemyType
{
  EnemyType0
};

typedef struct
{
  Entity _entity;
  DLList *list;
  enum EnemyType type;
  Bullets *bullets;
} Enemy;

Enemy *Enemy_create(DLList *list, enum EnemyType type, Bullets *bullets);
void Enemy_update(Enemy *e);
void Enemy_destroy(Enemy *e);