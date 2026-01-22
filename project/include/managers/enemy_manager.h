#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "entities/enemy.h"

#define MAX_ENEMY 20

typedef struct EnemyManager {
  Enemy enemy[MAX_ENEMY];
} EnemyManager;

void nm_active(EnemyManager *nm, Vector2 position, int size, float speed, Color color, uint32_t flags);
void nm_update(EnemyManager *nm, Map *map, ProjectileManager *pm, Vector2 playerPos, float playerSize, float dt);
void nm_draw(EnemyManager *nm);

#endif // ENEMY_MANAGER_H
