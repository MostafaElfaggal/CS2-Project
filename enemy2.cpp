#include "enemy2.h"

Enemy2::Enemy2(int x_pos, int y_pos) : Enemy(x_pos, y_pos, "Enemy.png")
{

}

void Enemy2::update(int frame) {
    if (frame%6 == 0)
    {
        int i = rand()%4;
        int check = checkStep((direction)i);

        while(check != 0 && check != -1)
        {
            i++;
            i%=4;
            check = checkStep((direction)i);
        }
            setDir((direction)i);
            Move((direction)i);
            if (rand()%10 == 0) {
                Shoot(false);
            }
    }
    Enemy::update(frame);
}
