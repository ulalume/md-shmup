#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <genesis.h>
#include "entity.h"

void Player_joyHandler(Entity *player, u16 joy, u16 changed, u16 state);
void Player_update(Entity *player);

#endif // _PLAYER_H_