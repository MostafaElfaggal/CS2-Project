#include "healthpot.h"

HealthPot::HealthPot(float x_pos, float y_pos) : GameItem(x_pos, y_pos, "RedFlask_1.png")
{
    for (int i=0; i<4; i++)
    {
        as.push_back(QPixmap("RedFlask_" + QString::number(i+1) + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }

    itype = PotHealth;

    setZValue(3);
}
