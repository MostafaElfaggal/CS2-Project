#include "coin.h"

Coin::Coin(float x_pos, float y_pos) : GameItem(x_pos+10, y_pos+10, "coin_1.png")
{
    for (int i=0; i<6; i++)
    {
        as.push_back(QPixmap("coin_" + QString::number(i+1) + ".png"));
        as[i] = as[i].scaledToHeight(30);
        as[i] = as[i].scaledToWidth(30);
    }

    itype = coin;

    setZValue(3);
}
