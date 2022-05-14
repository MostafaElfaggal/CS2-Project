#include "shield.h"

Shield::Shield(float x_pos, float y_pos) : GameItem(x_pos-(33-25), y_pos-(33-25), "Shield_01.png")
{
    effect = false;
    for (int i=0; i<20; i++)
    {
        as.push_back(QPixmap("Shield_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
        as[i] = as[i].scaledToHeight(66);
        as[i] = as[i].scaledToWidth(66);
    }

    itype = ShieldForceField;
}

void Shield::setLoc(float x_pos, float y_pos)
{
    GameObject::setLoc(x_pos-(33-25), y_pos-(33-25));
}

void Shield::setPtrs(Shield **s)
{
    self = s;
}

void Shield::updateFrame(long long frame) {
    if (current_animations==19)
            delete this;
//    else if (frame%3 == 0)
    else
        animate();
}

Shield::~Shield()
{
    *self = NULL;
}
