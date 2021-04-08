#pragma once

#include <genesis.h>
#include "entity.h"

void Player_joyHandler(Entity *player, u16 joy, u16 changed, u16 state);
void Player_update(Entity *player);
