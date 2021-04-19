#pragma once

typedef struct _scene Scene;
enum SceneName
{
  SceneNameGame
};

typedef void Scene_update(Scene *scene);
typedef void Scene_destory(Scene *scene);
typedef void Scene_nextScene(Scene *scene, enum SceneName name);
typedef void Scene_joyHandler(Scene *scene, u16 joy, u16 changed, u16 state);

typedef struct _scene
{
  enum SceneName name;
  Scene_update *update;
  Scene_destory *destroy;
  Scene_joyHandler *joyHandler;
  Scene_nextScene *onChangeNextScene;
} Scene;

Scene *nowScene;