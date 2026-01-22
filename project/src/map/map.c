#include "map/map.h"
#include "entities/enemy.h"
#include "managers/enemy_manager.h"
#include "map/tile.h"

#include <assert.h>
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <threads.h>

void map_init(Map *map, EnemyManager *nm)
{
  map->size = MAP_WIDTH * MAP_HEIGHT;
  map->nm = nm;
  map->tile = calloc(map->size, sizeof(Tile));
  if (map->tile == NULL) {
    perror("Error: failure while attempting to allocate mamory!\n");
    exit(EXIT_FAILURE);
  }

  map_load(map);
}

void map_destroy(Map *map) 
{
  if (map->tile == NULL) return;
  free(map->tile);
  map->tile = NULL;
}

void map_load(Map *map) 
{
  FILE *file = fopen("assets/map/level-1", "r");
  if (file == NULL) {
    perror("Error: the file could not be opened!\n");
    exit(EXIT_FAILURE);
  }
	
  int c;
  size_t i = 0;
  while ((c = fgetc(file)) != EOF && i < map->size) {
    if (c == '\n' || c == ' ' || c == '\0' || c == 0) continue;
    map_format(map, (char)c, i);
    i++;
  }
  if (i != map->size) { 
    perror("Error: Invalid Map Size!\n");
    exit(EXIT_FAILURE); 
  }
  fclose(file);
}

void map_format(Map *map, const char symbol, size_t index)
{
  switch (symbol) {
  case '.': 
    // map->tile[index].physics = 0;
    map->tile[index].color = BLACK;
    break;
  case '=':
    map->tile[index].physics = SOLID;
    map->tile[index].color = WHITE; 
    break;
  case '!':
    map->tile[index].color = BLACK;
    map_activeEnemy(map, (int)index, FOLLOW);
    break;
  case '@':
    map->tile[index].color = BLACK;
    map_activeEnemy(map, (int)index, SHOOTER);
    break;
  default:
    // map->tile[index].physics = 0;
    map->tile[index].color = GREEN; 
    break;
  }
}

bool map_hasFlags(Map *map, float x, float y, TileFlags flag)
{
  size_t index = map_getTileIndexAt(map, x, y);
  if (index >= map->size) return true;
  return (map->tile[index].physics & flag) == flag;
}

size_t map_getTileIndexAt(Map *map, float x, float y)
{
  if (x < 0 || y < 0) return map->size + 1;
  int tx = (int)(x / TILE_SIZE);
  int ty = (int)(y / TILE_SIZE);

  if (tx < 0 || tx >= MAP_WIDTH || ty < 0 || ty >= MAP_HEIGHT) return map->size + 1;
  return (size_t)ty * MAP_WIDTH + tx;
}

void map_activeEnemy(Map *map, size_t index, uint32_t flags)
{
  int size = 26;

  int x = (int)(index % MAP_WIDTH) * TILE_SIZE;
  int y = (int)(index / MAP_WIDTH) * TILE_SIZE;
  
  Vector2 position = {
    (x + (float)TILE_SIZE / 2) - ((float)size / 2),
    (y + (float)TILE_SIZE / 2) - ((float)size / 2)
  };

  float speed = 0;
  if ((flags & FOLLOW) == flags) speed = 180;
  else if ((flags & SHOOTER) == flags) speed = 2;
  
  nm_active(map->nm, position, size, speed, RED, flags);
}

void map_draw(Map *map) 
{
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      int posX = x * TILE_SIZE;
      int posY = y * TILE_SIZE;

      DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, map->tile[y * MAP_WIDTH + x].color);		
    }
  }
}
