#ifndef PLAYER_H
#define PLAYER_H

#include "map/map.h"
#include "raylib.h"

typedef struct {
	Vector2 position;
	Color color;
	int size;
	float speed;
} Player;

void player_init(Player *player);

void player_update(Player *player, Map *map, float dt);
void player_handleInput(Player *player, Map *map, float dt);
void player_chechHitbox(Player *player, Map *map, float dt, int dx, int dy);
void player_draw(Player *player);

#endif

