#include <genesis.h>
#include "sprite.h"
#include "entity.h"
#include "player.h"
#include "game_scene.h"

static Scene *gameScene = NULL;
static Entity *gameScenePlayer;

static void GameScene_joyHandler(u16 joy, u16 changed, u16 state)
{
  Player_joyHandler(gameScenePlayer, joy, changed, state);
}

static void GameScene_update()
{
  Player_update(gameScenePlayer);
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

  JOY_setEventHandler(NULL);
}

Scene *GameScene_create()
{
  GameScene_destory();

  VDP_setPalette(PAL1, player_sprite.palette->data);

  gameScenePlayer = MEM_alloc(sizeof(Entity));
  gameScenePlayer->x = 144;
  gameScenePlayer->y = 200;
  gameScenePlayer->w = 16;
  gameScenePlayer->h = 16;
  gameScenePlayer->velx = 0;
  gameScenePlayer->vely = 0;
  gameScenePlayer->health = 1;
  gameScenePlayer->sprite = SPR_addSprite(&player_sprite, gameScenePlayer->x, gameScenePlayer->y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
  ;

  VDP_drawText("v.0.0.2", 0, 0);
  JOY_setEventHandler(&GameScene_joyHandler);

  gameScene = (Scene *)MEM_alloc(sizeof(Scene));
  gameScene->name = SceneNameGame;
  gameScene->update = &GameScene_update;
  gameScene->destroy = &GameScene_destory;

  return gameScene;
}
