#include "managers/enemy_manager.h"
#include "entities/enemy.h"

void nm_active(EnemyManager *nm, Vector2 position, int size, float speed, Color color, uint32_t flags)
{
  for (int i = 0; i < MAX_ENEMY; i++) {
    if (nm->enemy[i].actived) continue;
    enemy_init(&nm->enemy[i], position, size, speed, color, flags);
    break;
  }
}

void nm_update(EnemyManager *nm, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt)
{
  for (int i = 0; i < MAX_ENEMY; i++) {
    if (!nm->enemy[i].actived) continue;

    nm->enemy[i].update(&nm->enemy[i], map, pm, playerPos, playerSize, dt);
  }
}

void nm_draw(EnemyManager *nm)
{
  for (int i = 0; i < MAX_ENEMY; i++) {
    if (!nm->enemy[i].actived) continue;
		
    nm->enemy[i].draw(&nm->enemy[i]);
  }
}
