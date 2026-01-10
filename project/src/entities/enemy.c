#include "entities/enemy.h"
#include "map/map.h"
#include "map/tile.h"

#include <math.h>
#include <raylib.h>


void enemy_init(Enemy *enemy, Vector2 position, int size, float speed, Color color, uint32_t flags)
{
	enemy->update = enemy_update;
	enemy->draw = enemy_draw;
	enemy->position = position;
	enemy->size = size;
	enemy->speed = speed;
	enemy->color = color;
	enemy->type = flags;
}

void enemy_update(Enemy *enemy, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt)
{
	enemy_movement(enemy, map, playerPos, playerSize, dt);
	// enemy_shoot(enemy, pm, playerPos, playerSize);
}

void enemy_movement(Enemy *enemy, Map *map, Vector2 playerPos, float playerSize, float dt)
{
	if ((enemy->type & FOLLOW) == 0) return;

	float cx = (playerPos.x + playerSize / 2) - (enemy->position.x + (float)enemy->size / 2);
	float cy = (playerPos.y + playerSize / 2) - (enemy->position.y + (float)enemy->size / 2);

	float distance = sqrt(cx * cx + cy * cy);
	if (distance < 8.0) return;
	
	float size = (float)enemy->size;

	int dx = 0;
	int dy = 0;
	
	if (enemy->position.x > playerPos.x) dx = -1;
	if (enemy->position.x < playerPos.x) dx = 1;
	if (enemy->position.y > playerPos.y) dy = -1;
	if (enemy->position.y < playerPos.y) dy = 1;

	float nextX = enemy->position.x + (cx / distance) * enemy->speed * dt;
	float nextY = enemy->position.y + (cy / distance) * enemy->speed * dt;

	float checkX = (dx > 0) ? nextX + size : nextX;
	float checkY = (dy > 0) ? nextY + size : nextY;

	if (!map_hasFlags(map, checkX, enemy->position.y, SOLID) && 
			!map_hasFlags(map, checkX, enemy->position.y + size, SOLID)) {
		enemy->position.x = nextX;
	}

	if (!map_hasFlags(map, enemy->position.x, checkY, SOLID) && 
			!map_hasFlags(map, enemy->position.x + size, checkY, SOLID)) {
		enemy->position.y = nextY;
	}
}

void enemy_shoot(Enemy *enemy, ProjectileManager *pm, Vector2 playerPos, float playerSize)
{
	
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
