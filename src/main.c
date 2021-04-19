#include "genesis.h"
#include "scene.h"
#include "game_scene.h"

void joyHandler(u16 joy, u16 changed, u16 state)
{
  nowScene->joyHandler(nowScene, joy, changed, state);
}

int main()
{
  SPR_init(0, 0, 0);
  JOY_init();

  nowScene = GameScene_create();

  JOY_setEventHandler(joyHandler);

  while (1)
  {
    nowScene->update(nowScene);

    SYS_doVBlankProcess();
  }

  nowScene->destroy(nowScene);
  nowScene = NULL;

  return 0;
}
