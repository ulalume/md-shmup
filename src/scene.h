#ifndef _SCENE_H_
#define _SCENE_H_

typedef void Scene_update();
typedef void Scene_destory();
typedef void Scene_nextScene(enum SceneName name);

enum SceneName {
  SceneNameGame
};

typedef struct {
  enum SceneName name;
  Scene_update * update;
  Scene_destory * destroy;
  Scene_nextScene * onChangeNextScene;
} Scene;
#endif // _SCENE_H_