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

static Scene *gameScene;
static Entity *gameScenePlayer;
static Stage1Background *gameSceneBackgroundStage1;
//static RasterBackground *gameSceneBackgroundRaster;

static Bullets *gameSceneBullets;
static Bullets *gameSceneEnemyBullets;

static DLList *enemyList;

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
  if (random() % 30 == 0)
  {
    Bullets_shoot(gameSceneEnemyBullets, 300, gameScenePlayer->y, -3, 0);
  }

  if (random() % 180 == 0)
  {
    Enemy *enemy = Enemy_create(enemyList, EnemyType0, gameSceneEnemyBullets);
    Entity *entity = (Entity *)enemy;
    entity->x = 300;
    entity->y = gameScenePlayer->y;
    entity->velx = -1;
  }

  Stage1Background_update(gameSceneBackgroundStage1);
  //RasterBackground_update(gameSceneBackgroundRaster);

  Enemy *en = (Enemy *)enemyList->first;
  while (en != NULL)
  {
    Enemy *next = (Enemy *)((DLListNode *)en)->next;
    Enemy_update(en);
    en = next;
  }

  Player_update(gameScenePlayer);
  Bullets_update(gameSceneBullets);
  Bullets_update(gameSceneEnemyBullets);

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
    Entity_destroy(gameScenePlayer);
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
  if (gameSceneEnemyBullets != NULL)
  {
    Bullets_destroy(gameSceneEnemyBullets);
    gameSceneEnemyBullets = NULL;
  }
  if (gameSceneBullets != NULL)
  {
    Bullets_destroy(gameSceneBullets);
    gameSceneBullets = NULL;
  }

  if (enemyList != NULL)
  {
    DLListNode *n = enemyList->first;
    while (n != NULL)
    {
      Enemy *enemy = (Enemy *)n;
      Enemy_destroy(enemy);
      n = n->next;
    }
    MEM_free(enemyList);
  }

  JOY_setEventHandler(NULL);
}

static void GameScene_onCollidePlayerBullets(SimpleCollision *playerBulletCollision, SimpleCollision *enemyCollision)
{
  DLListNode *n = enemyList->first;
  while (n != NULL)
  {
    Enemy *enemy = (Enemy *)n;
    Entity *entity = (Entity *)n;
    if (entity->collision == enemyCollision)
    {
      Enemy_destroy(enemy);
      break;
    }
    n = n->next;
  }
  Bullets_onCollide(gameSceneBullets, playerBulletCollision);
}
static void GameScene_onCollideEnemyBullets(SimpleCollision *enemyBulletCollision, SimpleCollision *playerCollision)
{
  (void)playerCollision;
  gameScenePlayer->health--;
  Bullets_onCollide(gameSceneEnemyBullets, enemyBulletCollision);
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
  gameScenePlayer->collision = Collision_create(COLLISION_PLAYER, TRUE, 0, 0, 16, 16);
  //gameScenePlayer->collision->onCollide = GameScene_onCollidePlayer;

  // bullets
  gameSceneBullets = Bullets_init(&bullet_sprite, COLLISION_PLAYER_BULLET, GameScene_onCollidePlayerBullets);
  gameSceneEnemyBullets = Bullets_init(&bullet_sprite, COLLISION_ENEMY_BULLET, GameScene_onCollideEnemyBullets);

  enemyList = (DLList *)MEM_alloc(sizeof(DLList));

  // bg
  gameSceneBackgroundStage1 = Stage1Background_create(PAL2, &stage1_palette, BG_A, &stage1_map, 0, 0, -1, 0);
  /*
  gameSceneBackgroundRaster = RasterBackground_create(PAL2, BG_A, &space_image);
  */
  JOY_setEventHandler(&GameScene_joyHandler);

  gameScene = (Scene *)MEM_alloc(sizeof(Scene));
  gameScene->name = SceneNameGame;
  gameScene->update = &GameScene_update;
  gameScene->destroy = &GameScene_destory;

  return gameScene;
}
