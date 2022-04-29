#include "thunder.h"

Thunder::Thunder(float x_pos, float y_pos) : GameItem(x_pos, y_pos, "Thunderstrike_01.png")
{
    effect = false;
    for (int i=0; i<13; i++)
    {
        as.push_back(QPixmap("Thunderstrike_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }

    itype = ThunderStrike;
}

void Thunder::updateFrame(int frame) {
    if (frame%3 == 0 && current_animations == 6)
        effect = true;

    if (frame%3 == 0 && current_animations==12)
            delete this;
    else
        GameItem::updateFrame(frame);
}


Thunder::~Thunder()
{
    Flame* f = new Flame(x(), y());
    scene()->addItem(f);
}
