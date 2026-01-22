#include "aplication.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "entities/projectile.h"
#include "managers/enemy_manager.h"
#include "managers/projectile_manager.h"
#include "map/map.h"
#include "utils/collision.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void app_init(App *app) 
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game enginee 2D");
  SetTargetFPS(FPS);

  map_init(&app->map, &app->nm);
  player_init(&app->player);
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
    float dt = GetFrameTime();

    app_update(app, dt);
    app_draw(app);
    app_checkCollision(app);
  }
}

void app_update(App *app, float dt)
{	
  player_update(&app->player, &app->map, &app->pm, dt);
  nm_update(&app->nm, &app->map, &app->pm, app->player.position, app->player.size, dt);
  pm_update(&app->pm, &app->map, dt);

  if (app->player.health == 0) {
    printf("player morreu e foi reiniciada o seu hp\n");
    app->player.health = 100;
  }
}

void app_checkCollision(App *app)
{
  for (int i = 0; i < MAX_PROJECTILES; i++) {

    if (!app->pm.projectile[i].actived) continue;

    // take damage player
    if ((app->pm.projectile[i].type & ENEMY) == ENEMY) {
      if (checkCollision(app->player.position,
			 (float)app->player.size,
			 app->pm.projectile[i].position,
			 (float)app->pm.projectile[i].size)) {

	player_takeDamage(&app->player, 8.5);
	app->pm.projectile[i].actived = false;
      }
    }

    // take damage enemy
    else if ((app->pm.projectile[i].type & PLAYER) == PLAYER) {

      for (int j = 0; j < MAX_ENEMY; j++) {
	if (!app->nm.enemy[j].actived) continue;
	if (checkCollision(app->nm.enemy[j].position,
			   (float)app->nm.enemy[j].size,
			   app->pm.projectile[i].position,
			   (float)app->pm.projectile[i].size)) {
	  
	  enemy_takeDamage(&app->nm.enemy[j], 15.5);
	  app->pm.projectile[i].actived = false;
	}
      }
    }
  }

  for (int i = 0; i < MAX_ENEMY; i++) {
    if (!app->nm.enemy[i].actived) continue;

    if (checkCollision(app->player.position,
                       (float)app->player.size,
                       app->nm.enemy[i].position,
                       (float)app->nm.enemy[i].size)) {

      player_takeDamage(&app->player, 5.0);
    }
  }
  
}

void app_draw(App *app)
{
  BeginDrawing();
  ClearBackground(BLACK);

  map_draw(&app->map);
  player_draw(&app->player);
  nm_draw(&app->nm);
  pm_draw(&app->pm);

  DrawFPS(10, 7);
  EndDrawing();
}
