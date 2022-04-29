#include "flame.h"

Flame::Flame(float x_pos, float y_pos) : GameItem(x_pos+13, y_pos+18, "FlameStart_01.png")
{
    for (int i=0; i<4; i++)
    {
        as[0].push_back(QPixmap("FlameStart_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
//        as[0][i] = as[0][i].scaledToHeight(50);
//        as[0][i] = as[0][i].scaledToWidth(50);
    }
    for (int i=0; i<8; i++)
    {
        as[1].push_back(QPixmap("FlameLoop_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
//        as[1][i] = as[1][i].scaledToHeight(50);
//        as[1][i] = as[1][i].scaledToWidth(50);
    }
    for (int i=0; i<5; i++)
    {
        as[2].push_back(QPixmap("FlameEnd_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
//        as[2][i] = as[2][i].scaledToHeight(50);
//        as[2][i] = as[2][i].scaledToWidth(50);
    }

    current = 0;
    animations = &as[0];

    itype = FlameWisp;
}

void Flame::updateFrame(int frame) {
    if (frame%12 == 0)
        effect = true;

    if (frame%3 == 0)
    {
        if (current == 3)
        {
            animations = &as[1];
            current_animations = 0;
        } else if (current == 11)
        {
            animations = &as[2];
            current_animations = 0;
        }

        if (current == 16)
            delete this;
        else
        {
            current++;
            animate();
        }
    }
}
