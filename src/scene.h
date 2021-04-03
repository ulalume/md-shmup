#ifndef _SCENE_H_
#define _SCENE_H_
typedef void Scene_update();
typedef void Scene_destory();
typedef struct {
  Scene_update * update;
  Scene_destory * destroy;
} Scene;
#endif // _SCENE_H_