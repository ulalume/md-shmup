#include "genesis.h"
#include "scene.h"
#include "game_scene.h"

Scene *scene;
int main()
{
  SPR_init(0, 0, 0);
  JOY_init();

  scene = GameScene_create();

  while (1)
  {
    scene->update();

    SYS_doVBlankProcess();
  }

  scene->destroy();
  scene = NULL;

  return 0;
}
