
#include "entity.h"
#include "bullets.h"
#include "enemy.h"
#include "const.h"
#include "sprites.h"

Enemy *Enemy_create(DLList *list, enum EnemyType type, Bullets *bullets)
{
  Enemy *enemy = (Enemy *)MEM_alloc(sizeof(Enemy));

  Entity *entity = (Entity *)enemy;
  entity->x = 0;
  entity->y = -16;
  entity->w = 16;
  entity->h = 16;
  entity->velx = 0;
  entity->vely = 0;
  entity->health = 1;
  entity->sprite = SPR_addSprite(&player_sprite, entity->x, entity->y, TILE_ATTR(PAL1, 0, FALSE, TRUE));
  entity->collision = Collision_create(COLLISION_ENEMY, TRUE, 0, 0, 16, 16, entity);

  enemy->list = list;
  DLList_add(list, (DLListNode *)enemy);

  enemy->bullets = bullets;
  enemy->type = type;

  return enemy;
}
void Enemy_update(Enemy *e)
{
  Entity *entity = (Entity *)e;
  Entity_update(entity);

  if (entity->y + entity->h < ENEMY_TOP_EDGE || entity->y > ENEMY_BOTTOM_EDGE ||
      entity->x + entity->w < ENEMY_LEFT_EDGE || entity->x > ENEMY_RIGHT_EDGE)
  {
    Enemy_destroy(e);
  }
}
void Enemy_destroy(Enemy *e)
{
  DLList_remove(e->list, (DLListNode *)e);

  Entity *entity = (Entity *)e;
  Entity_destroy(entity);
  MEM_free(e);
}