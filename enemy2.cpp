#include "enemy2.h"

Enemy2::Enemy2(int x_pos, int y_pos) : Enemy(x_pos, y_pos, "Enemy.png")
{

}

void Enemy2::update(int frame) {
    if (frame%6 == 0)
    {
            Move((direction)(rand()%4));
            // check collision
    }
    Enemy::update(frame);
}
