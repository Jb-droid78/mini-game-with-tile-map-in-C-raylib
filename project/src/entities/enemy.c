#include "entities/enemy.h"
#include "entities/projectile.h"
#include "managers/projectile_manager.h"
#include "map/map.h"
#include "map/tile.h"
#include "utils/clamp.h"

#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

void enemy_init(Enemy *enemy, Vector2 position, int size, float speed, Color color, uint32_t flags)
{
  enemy->update = enemy_update;
  enemy->draw = enemy_draw;
  
  enemy->position = position;
  enemy->size = size;
  enemy->speed = speed;
  enemy->color = color;
  enemy->type = flags;
  enemy->health = 100;
  enemy->attackTime = 0;
  enemy->iFrameTime = 0;
  enemy->actived = true;
}

void enemy_update(Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt)
{
  if (enemy->health == 0) { 
    enemy->actived = false;
    return;
  }

  if (enemy->iFrameTime > 0) {
    enemy->iFrameTime -= dt;
    if (enemy->iFrameTime < 0) enemy->iFrameTime = 0;
  }
  
  if (enemy->attackTime > 0) {
    enemy->attackTime -= dt;
    if (enemy->attackTime < 0) enemy->attackTime = 0; 
  }

  if (enemy->type & FOLLOW)  enemy_follow(enemy, map, playerPos, playerSize, dt);
  if (enemy->type & SHOOTER) enemy_shoot(enemy, map, pm, playerPos, playerSize, dt);
}

void enemy_movement(Enemy *enemy, Map *map, float valueX, float valueY, float dt)
{
  float size = (float)enemy->size;
					
  float velX = valueX * enemy->speed * dt;
  float velY = valueY * enemy->speed * dt;
	
  int dx = (velX > 0) ? 1 : (velX < 0 ? -1 : 0);
  int dy = (velY > 0) ? 1 : (velY < 0 ? -1 : 0); 

  float nextX = enemy->position.x + velX;
  float checkX = (dx > 0) ? nextX + size : nextX;

  if (!map_hasFlags(map, checkX, enemy->position.y, SOLID) && 
      !map_hasFlags(map, checkX, enemy->position.y + size, SOLID)) {
    enemy->position.x = nextX;
  }

  float nextY = enemy->position.y + velY;
  float checkY = (dy > 0) ? nextY + size : nextY;

  if (!map_hasFlags(map, enemy->position.x, checkY, SOLID) && 
      !map_hasFlags(map, enemy->position.x + size, checkY, SOLID)) {
    enemy->position.y = nextY;
  }
}

void enemy_shoot(Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt)
{
  float cx = 0;
  float cy = 0;
  enemy_calcDifference(enemy, playerPos, playerSize, &cx, &cy, SHOOTER);

  float erro = clamp(cy, -50, 50);
  if (erro > 9.f || erro < -9.f) enemy_movement(enemy, map, cx, erro, dt);
  if (enemy->attackTime > 0) return;
	
  if (!(erro > -40 && erro < 40)) return;
  Vector2 position = {
    enemy->position.x + (float)(enemy->size) / 4,
    enemy->position.y + (float)(enemy->size) / 4
  };

  Direction dir;
  if (enemy->position.x > playerPos.x) dir = LEFT;
  else if (enemy->position.x < playerPos.x) dir = RIGHT;
  else dir = NONE;

  enemy->attackTime = ENEMY_ATTACK_TIME;
  pm_active(pm, position, (int)(enemy->size / 2), 290, dir, PURPLE, ENEMY);
}

void enemy_follow(Enemy *enemy, Map *map, Vector2 playerPos, float playerSize, float dt)
{
  float cx = 0;
  float cy = 0;
  enemy_calcDifference(enemy, playerPos, playerSize, &cx, &cy, FOLLOW);
	
  float distance = sqrt(cx * cx + cy * cy);
  if (distance < 8.f || cx == 0.f || cy == 0.f) return;

  float dx = (cx / distance);
  float dy = (cy / distance);
  enemy_movement(enemy, map, dx, dy, dt);
}

void enemy_calcDifference(Enemy *enemy, Vector2 playerPos, float playerSize, float *cx, float *cy, uint32_t flag)
{
  float cyCalc = (playerPos.y + playerSize / 2) - (enemy->position.y + (float)enemy->size / 2);
  float cxCalc = (playerPos.x + playerSize / 2) - (enemy->position.x + (float)enemy->size / 2);

  if (flag & SHOOTER) { *cy = cyCalc;	} 
  if (flag & FOLLOW) { *cx = cxCalc; *cy = cyCalc; }
}

void enemy_takeDamage(Enemy *enemy, float damage)
{
  if (enemy->iFrameTime > 0 || !enemy->actived) return;

  enemy->health -= damage;
  if (enemy->health < 0) enemy->health = 0;
  
  enemy->iFrameTime = ENEMY_IFRAME_TIME;
}
  
void enemy_draw(Enemy *enemy)
{
  DrawRectangle(
	      (int)enemy->position.x, 
	      (int)enemy->position.y, 
	      enemy->size, 
	      enemy->size, 
	      enemy->color
	      );
}
