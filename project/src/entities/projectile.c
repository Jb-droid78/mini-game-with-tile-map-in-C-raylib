#include "entities/projectile.h"
#include "map/map.h"
#include "map/tile.h"

#include <raylib.h>
#include <stdbool.h>

void projectile_init(Projectile *projectile, Vector2 position, int size, float speed, Direction dir, Color color, uint32_t flags) 
{
	projectile->update = projectile_update;
	projectile->draw = projectile_draw;
	projectile->actived = true;
	projectile->color = color;
	projectile->position = position;
	projectile->dir = dir;
	projectile->size = size;
	projectile->speed = speed;
	projectile->type = flags; 
}

void projectile_update(Projectile *projectile, Map *map, float dt) 
{
	projectile_movement(projectile, map, dt);
}

void projectile_movement(Projectile *projectile, Map *map, float dt) 
{
	switch (projectile->dir) {
		case UP:    projectile->position.y -= projectile->speed * dt; break;
		case DOWN:  projectile->position.y += projectile->speed * dt; break;
		case LEFT:  projectile->position.x -= projectile->speed * dt; break;
		case RIGHT: projectile->position.x += projectile->speed * dt; break;
	}

	if (map_hasFlags(map, projectile->position.x, projectile->position.y, SOLID) ||
			map_hasFlags(map, projectile->position.x + (float)projectile->size, projectile->position.y, SOLID) ||
			map_hasFlags(map, projectile->position.x, projectile->position.y + (float)projectile->size, SOLID)) {
		projectile->actived = false;
	}
}

void projectile_draw(Projectile *projectile) 
{
	DrawRectangle(
		(int)projectile->position.x, 
		(int)projectile->position.y, 
		projectile->size, 
		projectile->size, 
		projectile->color
	);
}
