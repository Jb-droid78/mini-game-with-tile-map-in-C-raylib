#ifndef PLAYER_H
#define PLAYER_H

#include "map/map.h"
#include "projectile.h"
#include "managers/projectile_manager.h"

#include <raylib.h>

#define ATTACK_TIME 0.25

typedef struct Player {
	Vector2 position;
	Color color;
	int size;
	float speed;
	float attackTime;
} Player;

void player_init(Player *player);

void player_update(Player *player, Map *map, ProjectileManager *pm, float dt);
void player_handleInput(Player *player, Map *map, ProjectileManager *pm, float dt);
void player_chechHitbox(Player *player, Map *map, float dt, int dx, int dy);
void player_shoot(Player *player, ProjectileManager *pm, Direction dir);
void player_draw(Player *player);

#endif // PLAYER_H

