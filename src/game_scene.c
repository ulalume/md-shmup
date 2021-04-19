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
#include "enemy.h"
#include "scene.h"

static void GameScene_joyHandler(Scene *scene, u16 joy, u16 changed, u16 state)
{
  GameScene *gameScene = (GameScene *)scene;
  Player_joyHandler(gameScene->player, joy, changed, state);
  if (joy == JOY_1)
  {
    if (state & BUTTON_B & changed)
    {
      Bullets_shoot(gameScene->bullets, gameScene->player->x, gameScene->player->y, 3, 0);
    }
  }
}

static void GameScene_update(Scene *scene)
{
  GameScene *gameScene = (GameScene *)scene;
  if (random() % 30 == 0)
  {
    Bullets_shoot(gameScene->enemyBullets, 300, gameScene->player->y, -3, 0);
  }

  if (random() % 180 == 0)
  {
    Enemy *enemy = Enemy_create(gameScene->enemies, EnemyType0, gameScene->enemyBullets);
    Entity *entity = (Entity *)enemy;
    entity->x = 300;
    entity->y = gameScene->player->y;
    entity->velx = -1;
  }

  Stage1Background_update(gameScene->background);
  //RasterBackground_update(gameSceneBackgroundRaster);

  Enemy *en = (Enemy *)gameScene->enemies->first;
  while (en != NULL)
  {
    Enemy *next = (Enemy *)((DLListNode *)en)->next;
    Enemy_update(en);
    en = next;
  }

  Player_update(gameScene->player);
  Bullets_update(gameScene->bullets);
  Bullets_update(gameScene->enemyBullets);

  Collision_update();

  SPR_update();
}

static void GameScene_destory(Scene *scene)
{
  GameScene *gameScene = (GameScene *)scene;
  if (gameScene != NULL)
  {
    MEM_free(gameScene);
    gameScene = NULL;
  }

  if (gameScene->player != NULL)
  {
    Entity_destroy(gameScene->player);
  }

  if (gameScene->background != NULL)
  {
    Stage1Background_destroy(gameScene->background);
    gameScene->background = NULL;
  }
  /*
  if (gameSceneBackgroundRaster != NULL)
  {
    RasterBackground_destroy(gameSceneBackgroundRaster);
    gameSceneBackgroundRaster = NULL;
  }
  */
  if (gameScene->enemyBullets != NULL)
  {
    Bullets_destroy(gameScene->enemyBullets);
    gameScene->enemyBullets = NULL;
  }
  if (gameScene->bullets != NULL)
  {
    Bullets_destroy(gameScene->bullets);
    gameScene->bullets = NULL;
  }

  if (gameScene->enemies != NULL)
  {
    DLListNode *n = gameScene->enemies->first;
    while (n != NULL)
    {
      Enemy *enemy = (Enemy *)n;
      Enemy_destroy(enemy);
      n = n->next;
    }
    MEM_free(gameScene->enemies);
  }
}

static void GameScene_onCollidePlayerBullets(SimpleCollision *playerBulletCollision, SimpleCollision *enemyCollision)
{
  GameScene *gameScene = (GameScene *)nowScene;

  Enemy *enemy = (Enemy *)enemyCollision->entity;

  Enemy_destroy(enemy);
  Bullets_onCollide(gameScene->bullets, playerBulletCollision);
}
static void GameScene_onCollideEnemyBullets(SimpleCollision *enemyBulletCollision, SimpleCollision *playerCollision)
{
  GameScene *gameScene = (GameScene *)nowScene;

  (void)playerCollision;
  gameScene->player->health--;
  Bullets_onCollide(gameScene->enemyBullets, enemyBulletCollision);
}

Scene *GameScene_create()
{
  VDP_setPalette(PAL1, player_sprite.palette->data);

  GameScene *gameScene = (GameScene *)MEM_alloc(sizeof(GameScene));
  // player create
  gameScene->player = (Entity *)MEM_alloc(sizeof(Entity));
  gameScene->player->x = 144;
  gameScene->player->y = 200;
  gameScene->player->w = 16;
  gameScene->player->h = 16;
  gameScene->player->velx = 0;
  gameScene->player->vely = 0;
  gameScene->player->health = 1;
  gameScene->player->sprite = SPR_addSprite(&player_sprite, gameScene->player->x, gameScene->player->y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
  gameScene->player->collision = Collision_create(COLLISION_PLAYER, TRUE, 0, 0, 16, 16, gameScene->player);
  //gameScene->player->collision->onCollide = GameScene_onCollidePlayer;

  // bullets
  gameScene->bullets = Bullets_init(&bullet_sprite, COLLISION_PLAYER_BULLET, GameScene_onCollidePlayerBullets);
  gameScene->enemyBullets = Bullets_init(&bullet_sprite, COLLISION_ENEMY_BULLET, GameScene_onCollideEnemyBullets);

  gameScene->enemies = (DLList *)MEM_alloc(sizeof(DLList));

  // bg
  gameScene->background = Stage1Background_create(PAL2, &stage1_palette, BG_A, &stage1_map, 0, 0, -1, 0);
  /*
  gameSceneBackgroundRaster = RasterBackground_create(PAL2, BG_A, &space_image);
  */

  Scene *scene = (Scene *)gameScene;
  scene->name = SceneNameGame;
  scene->update = &GameScene_update;
  scene->destroy = &GameScene_destory;
  scene->joyHandler = &GameScene_joyHandler;

  return scene;
}
