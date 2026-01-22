#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include <stdbool.h>

static inline bool checkCollision(Vector2 a, float sizea, Vector2 b, float sizeb)
{
    return (a.x < b.x + sizeb &&
            a.x + sizea > b.x &&
            a.y < b.y + sizeb &&
            a.y + sizea > b.y);
}


#endif
