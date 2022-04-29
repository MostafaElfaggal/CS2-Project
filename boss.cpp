#include "boss.h"

Boss::Boss(float x_pos, float y_pos, int r) : Enemy(x_pos, y_pos, "BlueBoss_01.png", 1000, 15, 25, r)
{
    for (int i=0; i<3; i++)
    {
        as.push_back(QPixmap("BlueBoss_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }

    animations = &as;

    isExplode = false;
}

void Boss::update(int frame)
{
//    if (frame%3 == 0)
//        animations = &as[dir];

    if (frame % 10 == 0)
    {
        int i = rand() % 4;

        while (checkStep((direction)i) != 0)
        {
            i++;
            i %= 4;
        }
        setDir((direction)i);
        Move((direction)i);
    }
    if (rand() % 25 == 0)
        Shoot(false);

    if (frame%3 == 0)
        animate();

    Enemy::update(frame);
}
