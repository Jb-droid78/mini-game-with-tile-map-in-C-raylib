#ifndef ENEMY_H
#define ENEMY_H

typedef struct Map Map;
typedef struct ProjectileManager ProjectileManager;

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

#define ENEMY_ATTACK_TIME 0.45
#define ENEMY_IFRAME_TIME 0.65

typedef enum {
  SHOOTER = 0b0001,
  FOLLOW  = 0b0010,
} EnemyFlags;

typedef struct Enemy {
  Vector2 position;
  int size;
  float speed;
  uint32_t type;
  Color color;
  float health;
  float attackTime;
  float iFrameTime;
  bool actived;

  void (*update)(struct Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt);
  void (*draw)(struct Enemy *enemy);
} Enemy;

void enemy_init(Enemy *enemy, Vector2 position, int size, float speed, Color color, uint32_t flags);
void enemy_update(Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt);
void enemy_movement(Enemy *enemy, Map *map, float valueX, float valueY, float dt);
void enemy_shoot(Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt);
void enemy_follow(Enemy *enemy, Map *map, Vector2 playerPos, float playerSize, float dt);
void enemy_calcDifference(Enemy *enemy, Vector2 playerPos, float playerSize, float *cx, float *cy, uint32_t flag);
void enemy_takeDamage(Enemy *enemy, float damage);
void enemy_draw(Enemy *enemy);

#endif // ENEMY_H
