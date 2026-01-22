#ifndef MAP_H
#define MAP_H
 
#include "tile.h"

typedef struct EnemyManager EnemyManager; 

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAP_WIDTH 36
#define MAP_HEIGHT 23

typedef struct Map {
  Tile *tile;
  size_t size;
  EnemyManager *nm;
} Map;

void map_init(Map *map, EnemyManager *nm);
void map_destroy(Map *map);
void map_load(Map *map);
void map_format(Map *map, const char symbol, size_t index);
bool map_hasFlags(Map *map, float x, float y, TileFlags flag);
size_t map_getTileIndexAt(Map *map, float x, float y);
void map_activeEnemy(Map *map, size_t index, uint32_t flags);
void map_draw(Map *map);

#endif // MAP_H
