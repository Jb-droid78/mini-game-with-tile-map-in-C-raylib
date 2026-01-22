#ifndef PLAYER_H
#define PLAYER_H

#include "projectile.h"
typedef struct Map Map;
typedef struct ProjectileManager ProjectileManager;

#include <raylib.h>

#define PLAYER_ATTACK_TIME 0.25
#define PLAYER_IFRAME_TIME 0.70

typedef struct Player {
  Vector2 position;
  Color color;
  float health;
  int size;
  float speed;
  float attackTime;
  float iFrameTime;
} Player;

void player_init(Player *player);

void player_update(Player *player, Map *map, ProjectileManager *pm, float dt);
void player_handleInput(Player *player, Map *map, ProjectileManager *pm, float dt);
void player_chechHitbox(Player *player, Map *map, float dt, int dx, int dy);
void player_shoot(Player *player, ProjectileManager *pm, Direction dir);
void player_takeDamage(Player *player, float damage);
void player_draw(Player *player);

#endif // PLAYER_H

