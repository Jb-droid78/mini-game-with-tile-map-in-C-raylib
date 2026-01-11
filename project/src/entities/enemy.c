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
	if      (enemy->type & FOLLOW)  enemy_movement(enemy, map, playerPos, playerSize, dt);
	else if (enemy->type & SHOOTER) enemy_shoot(enemy, pm, playerPos, playerSize);
	
}

void enemy_movement(Enemy *enemy, Map *map, Vector2 playerPos, float playerSize, float dt)
{

	float cx = (playerPos.x + playerSize / 2) - (enemy->position.x + (float)enemy->size / 2);
	float cy = (playerPos.y + playerSize / 2) - (enemy->position.y + (float)enemy->size / 2);

	float distance = sqrt(cx * cx + cy * cy);
	if (distance < 8.0) return;
	
	float size = (float)enemy->size;

	float velX = (cx / distance) * enemy->speed * dt;
	float velY = (cy / distance) * enemy->speed * dt;
	
	int dx = (velX > 0) ? 1 : (velY < 0 ? -1 : 0);
	int dy = (velY > 0) ? 1 : (velX < 0 ? -1 : 0);

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

void enemy_shoot(Enemy *enemy, ProjectileManager *pm, Vector2 playerPos, float playerSize)
{
	// fazer essa bomba logo
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
