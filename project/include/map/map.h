#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include <stdbool.h>
#include <stddef.h>

#define MAP_WIDTH 36
#define MAP_HEIGHT 23

typedef struct Map {
	Tile *tile;
	size_t size;
} Map;

void map_init(Map *map);
void map_destroy(Map *map);

void map_load(Map *map);
void map_format(Map *map, const char symbol, size_t index);

bool map_hasFlags(Map *map, float x, float y, TileFlags flag);
size_t map_getTileIndexAt(Map *map, float x, float y);

void map_draw(Map *map);

#endif // MAP_H
