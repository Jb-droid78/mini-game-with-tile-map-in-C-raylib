#ifndef APLICATION_H
#define APLICATION_H

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 690

typedef struct {
} App;

void app_init(App *app);
int  app_execute(App *app);
void app_destroy(App *app);

void app_runLoop(App *app);
void app_update(App *app, float dt);
void app_draw(App *app);

#endif
