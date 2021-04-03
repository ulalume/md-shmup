#include <genesis.h>
#include "game_scene.h"

Scene * s = NULL;


void GameScene_update () {
}

void GameScene_destory () {
  if (s != NULL) {
    MEM_free(s);
    s = NULL;
  }
}

Scene * GameScene_create () {
  GameScene_destory();
  //s = { &GameScene_update, &GameScene_destory };
  return s;
}
