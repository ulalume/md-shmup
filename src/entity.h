#pragma once

#include <genesis.h>

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;
	Sprite *sprite;
} Entity;

void Entity_kill(Entity *e);
void Entity_revive(Entity *e);
bool Entity_collide(Entity *a, Entity *b);
void Entity_update(Entity *e);
