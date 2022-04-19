#include "wall.h"

Wall::Wall(int x_pos, int y_pos) : GameObject(x_pos, y_pos, 50, 50, "Bricks.png")
{
    // define animations
    animations.push_back(QPixmap("Bricks.png"));
    animations[0] = animations[0].scaledToHeight(50);
    animations[0] = animations[0].scaledToWidth(50);

    animations.push_back(QPixmap("Grass.png"));
    animations[1] = animations[1].scaledToHeight(50);
    animations[1] = animations[1].scaledToWidth(50);
}

void Wall::update(int frame) {
    if (frame%30 == 0) {
        animate(); // use the animate function every second which will auto scroll through the different animations
    }
}

Wall::~Wall() {
}
