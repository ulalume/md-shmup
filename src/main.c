#include "genesis.h"
#include "sprite.h"

void joyHandler( u16 joy, u16 changed, u16 state);

int player_pos_x = 144;
int player_pos_y = 200;
int player_vel_x = 0;
int player_vel_y = 0;
int player_anim = 0;

int main(bool hardReset)
{
    Sprite* player;
    SPR_init(0, 0, 0);

    JOY_init();
    JOY_setEventHandler( &joyHandler );

    VDP_setPalette(PAL1, player_sprite.palette->data);

    player = SPR_addSprite(&player_sprite, player_pos_x, player_pos_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    VDP_drawText("v.0.0.1", 0, 0);

    while(TRUE)
    {
        player_pos_x += player_vel_x;
        player_pos_y += player_vel_y;
        player_anim = (player_anim + 1) % 3;
        
        SPR_setAnimAndFrame(player, 0, player_anim);
        SPR_setPosition(player, player_pos_x, player_pos_y);

        SPR_update();

        // always call this method at the end of the frame        
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
			player_vel_x = 1;
		}
		else if (state & BUTTON_LEFT)
		{
			player_vel_x = -1;
		}
        else {
            if( (changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT) ){
				player_vel_x = 0;
			}
        }

        if (state & BUTTON_UP)
        {
			player_vel_y = -1;
		}
        else if (state & BUTTON_DOWN) {
			player_vel_y = 1;
		}
        else {
            if( (changed & BUTTON_UP) | (changed & BUTTON_DOWN) ){
				player_vel_y = 0;
			}
        }
	}
}
