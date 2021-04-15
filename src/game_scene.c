#include <genesis.h>

#include "sprites.h"
#include "tiles.h"
#include "gfx.h"

#include "game_scene.h"
#include "stage1_background.h"
#include "raster_background.h"

#include "entity.h"
#include "player.h"
#include "bullets.h"

#include "collision.h"

static Scene *gameScene = NULL;
static Entity *gameScenePlayer = NULL;
static Stage1Background *gameSceneBackgroundStage1;
//static RasterBackground *gameSceneBackgroundRaster;

static Bullets *gameSceneBullets = NULL;

static void GameScene_joyHandler(u16 joy, u16 changed, u16 state)
{
  Player_joyHandler(gameScenePlayer, joy, changed, state);
  if (joy == JOY_1)
  {
    if (state & BUTTON_B & changed)
    {
      Bullets_shoot(gameSceneBullets, gameScenePlayer->x, gameScenePlayer->y, 3, 0);
    }
  }
}

static void GameScene_update()
{
  Stage1Background_update(gameSceneBackgroundStage1);
  //RasterBackground_update(gameSceneBackgroundRaster);
  Player_update(gameScenePlayer);
  Bullets_update(gameSceneBullets);

  Collision_update();

  SPR_update();
}

static void GameScene_destory()
{
  if (gameScene != NULL)
  {
    MEM_free(gameScene);
    gameScene = NULL;
  }

  if (gameScenePlayer != NULL)
  {
    SPR_end(gameScenePlayer->sprite);
    MEM_free(gameScenePlayer);
  }

  if (gameSceneBackgroundStage1 != NULL)
  {
    Stage1Background_destroy(gameSceneBackgroundStage1);
    gameSceneBackgroundStage1 = NULL;
  }
  /*
  if (gameSceneBackgroundRaster != NULL)
  {
    RasterBackground_destroy(gameSceneBackgroundRaster);
    gameSceneBackgroundRaster = NULL;
  }
*/
  if (gameSceneBullets != NULL)
  {
    Bullets_destroy(gameSceneBullets);
    gameSceneBullets = NULL;
  }

  JOY_setEventHandler(NULL);
}

Scene *GameScene_create()
{
  GameScene_destory();

  VDP_setPalette(PAL1, player_sprite.palette->data);

  // player create
  gameScenePlayer = (Entity *)MEM_alloc(sizeof(Entity));
  gameScenePlayer->x = 144;
  gameScenePlayer->y = 200;
  gameScenePlayer->w = 16;
  gameScenePlayer->h = 16;
  gameScenePlayer->velx = 0;
  gameScenePlayer->vely = 0;
  gameScenePlayer->health = 1;
  gameScenePlayer->sprite = SPR_addSprite(&player_sprite, gameScenePlayer->x, gameScenePlayer->y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

  // bullets
  gameSceneBullets = Bullets_create();

  // bg
  gameSceneBackgroundStage1 = Stage1Background_create(PAL2, &stage1_palette, BG_A, &stage1_map, 0, 0, -1, 0);
  /*
  s16 x[TABLE_LEN];
  s16 velx[TABLE_LEN];
  s16 s, ns;
  for (int i = 0; i < TABLE_LEN; i++)
  {
    x[i] = FIX16(0);
    velx[i] = random() % 12;
    do
    {
      ns = -((random() & 0x3F) + 10);
    } while (ns == s);
    velx[i] = ns;
  }
  gameSceneBackgroundRaster = RasterBackground_create(PAL2, BG_A, &space_image, x, 0, velx, 0);
  */
  JOY_setEventHandler(&GameScene_joyHandler);

  gameScene = (Scene *)MEM_alloc(sizeof(Scene));
  gameScene->name = SceneNameGame;
  gameScene->update = &GameScene_update;
  gameScene->destroy = &GameScene_destory;

  return gameScene;
}
