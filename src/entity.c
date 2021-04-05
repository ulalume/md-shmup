#include <genesis.h>
#include "entity.h"

void Entity_kill(Entity *e)
{
	e->health = 0;
	SPR_setVisibility(e->sprite, HIDDEN);
}

void Entity_revive(Entity *e)
{
	e->health = 1;
	SPR_setVisibility(e->sprite, VISIBLE);
}

bool Entity_collide(Entity *a, Entity *b)
{
	return a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h >= b->y;
}
