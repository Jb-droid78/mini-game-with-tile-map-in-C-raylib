#include "map/map.h"
#include "map/tile.h"

#include <assert.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void map_init(Map *map)
{
	map->size = MAP_WIDTH * MAP_HEIGHT;
	map->tile = calloc(map->size, sizeof(Tile));
	if (map->tile == NULL) {
		perror("Error: the file could not be opened!\n");
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
	
	size_t i = 0;
	int c;
	while ((c = fgetc(file)) != EOF && i < map->size) {
		if (c == '\n' || c == ' ' || c == '\0' || c == 0) continue;
		map_format(map, (char)c, i);
		i++;
	}
	
	fclose(file);
}

void map_format(Map *map, const char symbol, size_t index)
{
	switch (symbol) {
		case '.': 
			map->tile[index].physics = 0;
			map->tile[index].color = BLACK;
			break;
		case ':': 
			map->tile[index].physics = 0;
			map->tile[index].color = GRAY;
			break;
		case '#': 
			map->tile[index].physics = DAMAGE;
			map->tile[index].color = RED;
			break;
		case '=':
			map->tile[index].physics = SOLID;
			map->tile[index].color = WHITE; 
			break;
	}
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
