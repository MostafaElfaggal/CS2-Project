#include "enemy1.h"

Enemy1::Enemy1(int x_pos, int y_pos) : Enemy(x_pos, y_pos, "Enemy.png")
{

}

void Enemy1::update(int frame) {
    if (frame%6 == 0)
    {
        int i = rand()%4;

        while(checkStep((direction)i))
        {
            i++;
            i%=4;
        }
            Move((direction)i);
            if (rand()%10 == 0) {
                Shoot();
            }
    }
    Enemy::update(frame);
}
