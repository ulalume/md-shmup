#include <genesis.h>
#include "game_scene.h"

Scene * gameScene = NULL;


void GameScene_update () {
}

void GameScene_destory () {
  if (gameScene != NULL) {
    MEM_free(gameScene);
    gameScene = NULL;
  }
}

Scene * GameScene_create () {
  GameScene_destory();
  gameScene = (Scene *) MEM_alloc(sizeof(Scene));
  gameScene->update = &GameScene_update;
  gameScene->destroy = &GameScene_destory;
  return gameScene;
}
