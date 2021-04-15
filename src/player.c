#include <genesis.h>
#include "entity.h"

#define ANIM_STRAIGHT 0
#define ANIM_MOVE_DOWN 1
#define ANIM_MOVE_UP 2

void Player_joyHandler(Entity *player, u16 joy, u16 changed, u16 state)
{
  if (joy == JOY_1)
  {
    if (state & BUTTON_RIGHT)
    {
      player->velx = 1;
    }
    else if (state & BUTTON_LEFT)
    {
      player->velx = -1;
    }
    else
    {
      if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT))
      {
        player->velx = 0;
      }
    }

    if (state & BUTTON_UP)
    {
      player->vely = -1;
      SPR_setAnim(player->sprite, ANIM_MOVE_UP);
    }
    else if (state & BUTTON_DOWN)
    {
      player->vely = 1;
      SPR_setAnim(player->sprite, ANIM_MOVE_DOWN);
    }
    else
    {
      if ((changed & BUTTON_UP) | (changed & BUTTON_DOWN))
      {
        player->vely = 0;
        SPR_setAnim(player->sprite, ANIM_STRAIGHT);
      }
    }
  }
}

void Player_update(Entity *player)
{
  Entity_update(player);
}