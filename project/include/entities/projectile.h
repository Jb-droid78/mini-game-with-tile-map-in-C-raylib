#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "map/map.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef enum {
	PLAYER = (1 << 0),
	ENEMY  = (1 << 1),
} Flags;

typedef struct Projectile {
	Vector2 position;
	Direction dir;
	float speed;
	int size;
	
	bool actived;
	Color color;
	uint32_t type;

	void (*update)(struct Projectile *projectile, Map *map, float dt);
	void (*draw)(struct Projectile *projectile);
} Projectile; 

void projectile_init(Projectile *projectile, Vector2 position, int size, float speed, Direction dir, Color color, uint32_t flags);
void projectile_update(Projectile *projectile, Map *map, float dt);
void projectile_movement(Projectile *projectile, Map *map, float dt);
void projectile_draw(Projectile *projectile);

#endif // PROJECTILE_H
