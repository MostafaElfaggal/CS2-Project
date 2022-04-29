#include "wall.h"

Wall::Wall(int x_pos, int y_pos, int v) : GameObject(x_pos, y_pos, 50, 50, "wall_.png", "wall")
{
    value = v;
    setZValue(2);
}

void Wall::updateFrame(int frame){}

Wall::~Wall() {
}
