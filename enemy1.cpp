#include "enemy1.h"

Enemy1::Enemy1(int x_pos, int y_pos) : Enemy(x_pos, y_pos, "Horus1.png")
{
    // define animations
    for (int i=0; i<9; i++)
    {
        a1.push_back(QPixmap("Horus" + QString::number(i+1) + ".png"));
        a1[i] = a1[i].scaledToHeight(50);
        a1[i] = a1[i].scaledToWidth(50);
    }

    animations = &a1;
}

void Enemy1::update(int frame)
{
    if (frame%2 == 0) {
        animate(); // use the animate function every second which will auto scroll through the different animations
    }

    if (frame % 6 == 0)
    {
        int i = rand() % 4;

        while (checkStep((direction)i) != 0)
        {
            i++;
            i %= 4;
        }
        setDir((direction)i);
        Move((direction)i);
        if (rand() % 10 == 0)
        {
            Shoot(false);
        }
    }
    Enemy::update(frame);
}
