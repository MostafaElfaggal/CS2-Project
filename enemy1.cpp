#include "enemy1.h"

Enemy1::Enemy1(int x_pos, int y_pos) : Enemy(x_pos, y_pos, "monster1.png")
{

}

void Enemy1::update(int frame) {
    if (frame%6 == 0)
    {
            Move((direction)(rand()%4));
            if (rand()%10 == 0) {
                Shoot();
            }
            // check collision
    }
    Enemy::update(frame);
}
