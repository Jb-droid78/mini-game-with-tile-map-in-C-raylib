#include "entities/player.h"
#include "entities/projectile.h"
#include "managers/projectile_manager.h"
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
  player->attackTime = 0;
}

void player_update(Player *player, Map *map, ProjectileManager *pm, float dt) 
{
  if (player->attackTime > 0) {
    player->attackTime -= dt;
    if (player->attackTime < 0) player->attackTime = 0;
  }

  player_handleInput(player, map, pm, dt);
}

void player_handleInput(Player *player, Map *map, ProjectileManager *pm, float dt)
{
  int dx = 0;
  int dy = 0;

  if (IsKeyDown(KEY_W)) dy = -1;
  if (IsKeyDown(KEY_S)) dy = 1;
  if (IsKeyDown(KEY_A)) dx = -1;
  if (IsKeyDown(KEY_D)) dx = 1;
	
  player_chechHitbox(player, map, dt, dx, dy);

  if (player->attackTime > 0) return;
  if      (IsKeyDown(KEY_UP))    player_shoot(player, pm, UP);
  else if (IsKeyDown(KEY_DOWN))  player_shoot(player, pm, DOWN);
  else if (IsKeyDown(KEY_LEFT))  player_shoot(player, pm, LEFT);
  else if (IsKeyDown(KEY_RIGHT)) player_shoot(player, pm, RIGHT);
}

void player_chechHitbox(Player *player, Map *map, float dt, int dx, int dy)
{
  float nextX = player->position.x + dx * player->speed * dt;
  float nextY = player->position.y + dy * player->speed * dt;

  float checkX = (dx > 0) ? nextX + (float)player->size : nextX;
  float checkY = (dy > 0) ? nextY + (float)player->size : nextY;

  if (!map_hasFlags(map, checkX, player->position.y, SOLID) && 
      !map_hasFlags(map, checkX, player->position.y + (float)player->size, SOLID)) {	
    player->position.x = nextX;
  }

  if (!map_hasFlags(map, player->position.x, checkY, SOLID) &&
      !map_hasFlags(map, player->position.x + (float)player->size, checkY, SOLID)) {
    player->position.y = nextY;
  }
}

void player_shoot(Player *player, ProjectileManager *pm, Direction dir)
{
  Vector2 position = {
    player->position.x + (float)player->size / 4,
    player->position.y + (float)player->size / 4
  };

  player->attackTime = PLAYER_ATTACK_TIME;
  pm_active(pm, position, (int)(player->size / 2), 300, dir, BLUE, PLAYER);
}

void player_draw(Player *player)
{
  DrawRectangle((int)player->position.x, (int)player->position.y, player->size, player->size, player->color);
}
