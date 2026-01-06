#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include <stddef.h>

#define TILE_SIZE 30

typedef enum {
	SOLID  = 1 << 0,
	DAMAGE = 1 << 1,
} TileFlags;

typedef struct {
	int physics;
	Color color;
} Tile; 

#endif
