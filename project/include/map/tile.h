#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <stddef.h>

#define TILE_SIZE 30

typedef enum {
  SOLID  = 1 << 0,
} TileFlags;

typedef struct Tile {
  int physics;
  Color color;
} Tile; 

#endif // TILE_H
