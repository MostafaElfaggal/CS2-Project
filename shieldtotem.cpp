#include "shieldtotem.h"

ShieldTotem::ShieldTotem(float x_pos, float y_pos) : GameItem(x_pos, y_pos-25, "FireTotemStart_01.png")
{
    for (int i=0; i<8; i++)
    {
        as[0].push_back(QPixmap("FireTotemStart_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
//        as[0][i] = as[0][i].scaledToHeight(50);
        as[0][i] = as[0][i].scaledToWidth(50);
    }
    for (int i=0; i<7; i++)
    {
        as[1].push_back(QPixmap("FireTotemLoop_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
//        as[1][i] = as[1][i].scaledToHeight(50);
        as[1][i] = as[1][i].scaledToWidth(50);
    }
    for (int i=0; i<14; i++)
    {
        as[2].push_back(QPixmap("FireTotemExit_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
//        as[2][i] = as[2][i].scaledToHeight(50);
        as[2][i] = as[2][i].scaledToWidth(50);
    }

    current = 0;
    animations = &as[0];

    dying = false;

    itype = Shield_Totem;
    setZValue(3);
}

void ShieldTotem::updateFrame(long long frame) {
    effect = true;
//    if (frame%12 == 0)

    if (frame%2 == 0)
    {
        if (current == 7)
        {
            animations = &as[1];
            current_animations = 0;
        } else if (current == 77)
        {
            die();
        }

        if (current == 91)
            delete this;
        else
        {
            current++;
            animate();
        }
    }
}

void ShieldTotem::die()
{
    if (dying)
        return;
    current = 77;
    animations = &as[2];
    current_animations = 0;
    effect = false;
    dying = true;
}

ShieldTotem::~ShieldTotem()
{

}
