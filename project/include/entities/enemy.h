#ifndef ENEMY_H
#define ENEMY_H

#include "managers/projectile_manager.h"
#include "map/map.h"

#include <raylib.h>
#include <stdint.h>

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

	void (*update)(struct Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt);
	void (*draw)(struct Enemy *enemy);
} Enemy;

void enemy_init(Enemy *enemy, Vector2 position, int size, float speed, Color color, uint32_t flags);
void enemy_update(Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt);
void enemy_movement(Enemy *enemy, Map *map, Vector2 playerPos, float playerSize, float dt);
void enemy_shoot(Enemy *enemy, ProjectileManager *pm, Vector2 playerPos, float playerSize);
void enemy_draw(Enemy *enemy);

#endif // ENEMY_H
