#pragma once

#include "scene.h"
#include "entity.h"
#include "bullets.h"

#include "doubly_linked_list.h"
#include "stage1_background.h"

typedef struct
{
  Scene _scene;
  Entity *player;
  Stage1Background *background;
  //static RasterBackground *gameSceneBackgroundRaster;
  Bullets *bullets;
  Bullets *enemyBullets;
  DLList *enemies;
} GameScene;

Scene *GameScene_create();