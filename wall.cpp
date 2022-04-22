#include "wall.h"

Wall::Wall(int x_pos, int y_pos) : GameObject(x_pos, y_pos, 50, 50, "Bricks.png")
{
    // define animations
    a1.push_back(QPixmap("Bricks.png"));
    a1[0] = a1[0].scaledToHeight(50);
    a1[0] = a1[0].scaledToWidth(50);

    a1.push_back(QPixmap("Grass.png"));
    a1[1] = a1[1].scaledToHeight(50);
    a1[1] = a1[1].scaledToWidth(50);

    animations = &a1;
}

void Wall::update(int frame) {
//    if (frame%30 == 0) {
//        animate(); // use the animate function every second which will auto scroll through the different animations
//    }
}

Wall::~Wall() {
}
