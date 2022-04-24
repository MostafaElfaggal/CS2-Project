#include "enemy2.h"

Enemy2::Enemy2(int x_pos, int y_pos) : Enemy(x_pos, y_pos, "Horus1.png")
{
    for (int i=0; i<9; i++)
    {
        a1.push_back(QPixmap("Horus" + QString::number(i+1) + ".png"));
        a1[i] = a1[i].scaledToHeight(50);
        a1[i] = a1[i].scaledToWidth(50);
    }

    animations = &a1;
}

void Enemy2::update(int frame)
{
    if (frame%2 == 0) {
        animate(); // use the animate function every second which will auto scroll through the different animations
    }

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
