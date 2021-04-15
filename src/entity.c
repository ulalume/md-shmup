#include <genesis.h>
#include "entity.h"

void Entity_kill(Entity *e)
{
	e->health = 0;
	if (e->collision != NULL)
		e->collision->enabled = FALSE;
	SPR_setVisibility(e->sprite, HIDDEN);
}

void Entity_revive(Entity *e)
{
	e->health = 1;
	if (e->collision != NULL)
		e->collision->enabled = TRUE;
	SPR_setVisibility(e->sprite, VISIBLE);
}

void Entity_update(Entity *e)
{
	e->x += e->velx;
	e->y += e->vely;

	if (e->collision != NULL)
	{
		// 中心にする
		e->collision->x = e->x + (e->w - e->collision->w) / 2;
		e->collision->y = e->y + (e->h - e->collision->h) / 2;
	}

	if (e->sprite != NULL)
	{
		SPR_setPosition(e->sprite, e->x, e->y);
	}
}

void Entity_destroy(Entity *e)
{
	if (e->sprite != NULL)
	{
		SPR_releaseSprite(e->sprite);
	}
	if (e->collision != NULL)
	{
		Collision_destroy(e->collision);
	}
	MEM_free(e);
}