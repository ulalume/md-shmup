#include <genesis.h>

#include "sprites.h"
#include "tiles.h"
#include "gfx.h"

#include "game_scene.h"
#include "simple_background.h"
#include "stage1_background.h"
#include "entity.h"
#include "player.h"

#define MAX_BULLETS 6

#define RIGHT_EDGE 320
#define BOTTOM_EDGE 224

Entity *gameSceneBullets;
u16 gameSceneBulletsOnScreen = 0;

static Scene *gameScene = NULL;
static Entity *gameScenePlayer;
//static SimpleBackground *gameSceneBackground;
static Stage1Background *gameSceneBackgroundStage1;

static void initBullets()
{
  gameSceneBullets = (Entity *)MEM_alloc(sizeof(Entity) * MAX_BULLETS);

  int i = 0;
  Entity *b = gameSceneBullets;

  for (i = 0; i < MAX_BULLETS; i++)
  {
    b->x = 0;
    b->y = -10;
    b->w = 8;
    b->h = 8;
    b->velx = 0;
    b->vely = 0;
    b->sprite = SPR_addSprite(&bullet_sprite, i * 10, 0, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    Entity_kill(b);
    b++;
  }
}

static void shootBullet(int fromX, int fromY, int velx)
{
  if (gameSceneBulletsOnScreen >= MAX_BULLETS)
    return;

  Entity *b;
  u16 i = 0;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    b = &gameSceneBullets[i];

    if (b->health == 0)
    {
      b->x = fromX;
      b->y = fromY;
      b->velx = velx;

      Entity_revive(b);

      SPR_setPosition(b->sprite, b->x, b->y);
      gameSceneBulletsOnScreen++;

      break;
    }
  }
}

static void positionBullets()
{
  u16 i = 0;
  Entity *b;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    b = &gameSceneBullets[i];
    if (b->health > 0)
    {
      b->y += b->vely;
      b->x += b->velx;

      if (b->y + b->h < 0 || b->y > BOTTOM_EDGE ||
          b->x + b->x < 0 || b->x > RIGHT_EDGE)
      {
        Entity_kill(b);
        gameSceneBulletsOnScreen--;
      }
      else
      {
        SPR_setPosition(b->sprite, b->x, b->y);
      }
    }
  }
}

static void destroyBullets()
{
  Entity *b;
  u16 i = 0;
  for (i = 0; i < MAX_BULLETS; i++)
  {
    b = &gameSceneBullets[i];
    SPR_end(b->sprite);
    MEM_free(b);
  }
  gameSceneBullets = NULL;
}

static void GameScene_joyHandler(u16 joy, u16 changed, u16 state)
{
  Player_joyHandler(gameScenePlayer, joy, changed, state);
  if (joy == JOY_1)
  {
    if (state & BUTTON_B & changed)
    {
      shootBullet(gameScenePlayer->x, gameScenePlayer->y, 3);
    }
  }
}

static void GameScene_update()
{
  Stage1Background_update(gameSceneBackgroundStage1);
  Entity_update(gameScenePlayer);

  positionBullets();

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

  if (gameSceneBullets != NULL)
  {
    destroyBullets();
  }

  JOY_setEventHandler(NULL);
}

Scene *GameScene_create()
{
  GameScene_destory();

  VDP_setPalette(PAL1, player_sprite.palette->data);

  gameScenePlayer = (Entity *)MEM_alloc(sizeof(Entity));
  gameScenePlayer->x = 144;
  gameScenePlayer->y = 200;
  gameScenePlayer->w = 16;
  gameScenePlayer->h = 16;
  gameScenePlayer->velx = 0;
  gameScenePlayer->vely = 0;
  gameScenePlayer->health = 1;
  gameScenePlayer->sprite = SPR_addSprite(&player_sprite, gameScenePlayer->x, gameScenePlayer->y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

  initBullets();

  //gameSceneBackground = SimpleBackground_create(PAL2, BG_A, &space_image, 0, 0, -2, -1);
  gameSceneBackgroundStage1 = Stage1Background_create(PAL2, &stage1_palette, BG_A, &stage1_map, 0, 0, -1, 0);
  JOY_setEventHandler(&GameScene_joyHandler);

  gameScene = (Scene *)MEM_alloc(sizeof(Scene));
  gameScene->name = SceneNameGame;
  gameScene->update = &GameScene_update;
  gameScene->destroy = &GameScene_destory;

  return gameScene;
}
