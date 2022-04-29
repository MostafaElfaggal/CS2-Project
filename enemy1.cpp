#include "enemy1.h"

Enemy1::Enemy1(int x_pos, int y_pos, int r) : Enemy(x_pos, y_pos, "UndeadKingS_01.png", 100, 10, 25, r)
{
    // define animations
    QString chars[4] = {"N", "S", "E", "W"};
    for (int _=0; _<4; _++)
    for (int i=0; i<3; i++)
    {
        as[_].push_back(QPixmap("UndeadKing" + chars[_] + "_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
        as[_][i] = as[_][i].scaledToHeight(50);
        as[_][i] = as[_][i].scaledToWidth(50);
    }

    animations = &as[3];
}

void Enemy1::update(int frame)
{
    if (frame%3 == 0)
        animations = &as[dir];

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
