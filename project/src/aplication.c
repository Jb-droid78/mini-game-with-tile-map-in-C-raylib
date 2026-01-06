#include "aplication.h"
#include "map/map.h"

#include "raylib.h"
#include <stdlib.h>

void app_init(App *app) 
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game enginee 2D");
	SetTargetFPS(FPS);

	map_init(&app->map);
}

void app_destroy(App *app)
{
	map_destroy(&app->map);
	CloseWindow();
}

int app_execute(App *app)
{
	app_init(app);
	app_runLoop(app);
	app_destroy(app);
	return EXIT_SUCCESS;
}

void app_runLoop(App *app) 
{
	
	while (!WindowShouldClose()) {
		float	dt = GetFrameTime();

		app_update(app, dt);
		app_draw(app);
	}
}

void app_update(App *app, float dt)
{	
}

void app_draw(App *app)
{
	BeginDrawing();
	ClearBackground(BLACK);

	map_draw(&app->map);

	DrawFPS(10, 7);
	EndDrawing();
}


