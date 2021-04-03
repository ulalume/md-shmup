#include "genesis.h"
#include "sprite.h"
#include "entity.h"

#define ANIM_STRAIGHT   0
#define ANIM_MOVE_DOWN  1
#define ANIM_MOVE_UP    2

void joyHandler( u16 joy, u16 changed, u16 state);
Entity player = {144, 200, 16, 16, 0, 0, 1, NULL};

void Player_update(Entity * player) {
    player->x += player->velx;
    player->y += player->vely;
    
    SPR_setPosition(player->sprite, player->x, player->y);
}

int main(bool hardReset)
{
    VDP_drawText("v.0.0.2", 0, 0);

    SPR_init(0, 0, 0);

    VDP_setPalette(PAL1, player_sprite.palette->data);
    player.sprite = SPR_addSprite(&player_sprite, player.x, player.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

    JOY_init();
    JOY_setEventHandler( &joyHandler );

    while(1)
    {
        Player_update(&player);

        SPR_update();      
        SYS_doVBlankProcess();
    }

    return 0;
}

void joyHandler( u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1)
	{
		if (state & BUTTON_RIGHT)
		{
			player.velx = 1;
		}
		else if (state & BUTTON_LEFT)
		{
			player.velx = -1;
		}
        else {
            if( (changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT) ){
				player.velx = 0;
			}
        }

        if (state & BUTTON_UP)
        {
			player.vely = -1;
            SPR_setAnim(player.sprite, ANIM_MOVE_UP);
		}
        else if (state & BUTTON_DOWN) {
			player.vely = 1;
            SPR_setAnim(player.sprite, ANIM_MOVE_DOWN);
		}
        else {
            if( (changed & BUTTON_UP) | (changed & BUTTON_DOWN) ){
				player.vely = 0;
                SPR_setAnim(player.sprite, ANIM_STRAIGHT);
			}
        }
	}
}
