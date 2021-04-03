
#include <genesis.h>
#include "game_scene.h"

Scene * s = NULL;


Scene * GameScene_update () {
}

Scene * GameScene_destory () {
  if (s != NULL) {
    flee(s);
    s = NULL;
  }
}

Scene * GameScene_create () {
  GameScene_destory();
  s = { &GameScene_update, &GameScene_destory };
}
