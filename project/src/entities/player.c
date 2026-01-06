#include "entities/player.h"
#include "map/map.h"
#include "map/tile.h"

#include <raylib.h>

void player_init(Player *player)
{
	player->position.x = 500;
	player->position.y = 345;
	player->size = 20;
	player->speed = 230;
	player->color = GREEN;
}

void player_update(Player *player, Map *map, float dt) 
{
	player_handleInput(player, map, dt);
}

void player_handleInput(Player *player, Map *map, float dt)
{
	int dx = 0;
	int dy = 0;

	if (IsKeyDown(KEY_W)) dy = -1;
	if (IsKeyDown(KEY_S)) dy = 1;
	if (IsKeyDown(KEY_A)) dx = -1;
	if (IsKeyDown(KEY_D)) dx = 1;
	
	player_chechHitbox(player, map, dt, dx, dy);
}

void player_chechHitbox(Player *player, Map *map, float dt, int dx, int dy)
{
	float nextX = player->position.x + (dx * (player->speed * dt));
	float nextY = player->position.y + (dy * (player->speed * dt));

	float checkX = (dx > 0) ? nextX + player->size : nextX;
	float checkY = (dy > 0) ? nextY + player->size : nextY;

	if (!map_hasFlags(map, checkX, player->position.y, SOLID) || 
			!map_hasFlags(map, checkX, player->position.y + player->size, SOLID)) {	
		player->position.x = nextX;
	}

	if (!map_hasFlags(map, player->position.x, checkY, SOLID) ||
			!map_hasFlags(map, player->position.x + player->size, checkY, SOLID)) {
		player->position.y = nextY;
	}
}

void player_draw(Player *player)
{
	DrawRectangle((int)player->position.x, (int)player->position.y, player->size, player->size, player->color);
}
