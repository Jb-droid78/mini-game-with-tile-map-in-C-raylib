#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "entities/projectile.h"

#define MAX_PROJECTILES 100

typedef struct ProjectileManager {
  Projectile projectile[MAX_PROJECTILES];
} ProjectileManager;

void pm_active(ProjectileManager *pm, Vector2 position, int size, float speed, Direction dir, Color color, uint32_t flags);
void pm_update(ProjectileManager *pm, Map *map, float dt);
void pm_draw(ProjectileManager *pm);

#endif // PROJECTILE_MANAGER_H
