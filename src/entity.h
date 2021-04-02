#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <genesis.h>

typedef struct {
	int x;
	int y;
	int w;
	int h;
	int velx;
	int vely;
	int health;
	Sprite* sprite;
} Entity;

void Entity_kill(Entity * e);
void Entity_revive(Entity * e);

#endif // _ENTITY_H_