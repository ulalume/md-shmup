#include <genesis.h>
#include "entity.h"

void Entity_kill(Entity * e){
	e->health = 0;
	SPR_setVisibility(e->sprite, HIDDEN);
}

void Entity_revive(Entity * e){
	e->health = 1;
	SPR_setVisibility(e->sprite, VISIBLE);
}
