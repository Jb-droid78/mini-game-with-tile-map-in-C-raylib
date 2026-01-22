#include "managers/projectile_manager.h"
#include "entities/projectile.h"

void pm_active(ProjectileManager *pm, Vector2 position, int size, float speed, Direction dir, Color color, uint32_t flags)
{
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (pm->projectile[i].actived) continue;
    projectile_init(&pm->projectile[i], position, size, speed, dir, color, flags);
    break;
  }
}

void pm_update(ProjectileManager *pm, Map *map, float dt) 
{
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!pm->projectile[i].actived) continue;
		
    pm->projectile[i].update(&pm->projectile[i], map, dt);
  }
}

void pm_draw(ProjectileManager *pm) 
{
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (!pm->projectile[i].actived) continue;
		
    pm->projectile[i].draw(&pm->projectile[i]);
  }
}
