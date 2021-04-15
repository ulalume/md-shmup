#pragma once

#include <genesis.h>
#include "collision.h"
#include "doubly_linked_list.h"

typedef struct _entity Entity;

typedef struct _entity
{
	DLListNode _node;
	s16 x;
	s16 y;
	u16 w;
	u16 h;
	int velx;
	int vely;
	int health;

	Sprite *sprite;
	SimpleCollision *collision;
} Entity;

void Entity_kill(Entity *e);
void Entity_revive(Entity *e);
void Entity_update(Entity *e);

void Entity_destroy(Entity *e);