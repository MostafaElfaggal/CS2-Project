#include "boss.h"

Boss::Boss(float x_pos, float y_pos, int r, int x_loc, int y_loc) : Enemy(x_pos, y_pos, "BlueBoss_01.png", 1000, 15, 50, r, x_loc, y_loc)
{
//    g = ga;
    for (int i=0; i<3; i++)
    {
        as.push_back(QPixmap("BlueBoss_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }

    animations = &as;

    isExplode = false;
}

void Boss::updateFrame(long long frame)
{
//    if (frame%3 == 0)
//        animations = &as[dir];

    if (frame % 10 == 0)
    {
//        int i = rand() % 4;

//        int c = checkStep((direction)i);

//        while (c != 0 && c < 100)
//        {
//            i++;
//            i %= 4;
//            c = checkStep((direction)i);
//        }

//        int x_next, y_next;
//        g->shortestPath(x_next, y_next);
        int i=0;
        qDebug() << x_next << " " << y_next;

        if (!(x_next == loc[0] && y_next == loc[1])) // standing on player
        {
        if (x_next == loc[0] && y_next == loc[1]+1) // down
             i = 1;
        else if (x_next == loc[0] && y_next == loc[1]-1) // up
            i = 0;
        else if (x_next == loc[0]+1 && y_next == loc[1]) // right
            i = 2;
        else if (x_next == loc[0]-1 && y_next == loc[1]) // left
            i = 3;

        int c = checkStep((direction)i);
        if (!(c!=0 && c<100))
        {
            setDir((direction)i);
            Move((direction)i);
        }
        }
    }
    if (rand() % 10 == 0)
        Shoot(false);

    if (frame%3 == 0)
        animate();

    Enemy::updateFrame(frame);
}
