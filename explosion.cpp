#include "explosion.h"

Explosion::Explosion(float x_pos, float y_pos) : GameItem(x_pos, y_pos, "Explosion_1.png")
{
    current = 1;
    for (int i=0; i<4; i++)
    {
        as.push_back(QPixmap("Explosion_" + QString::number(i+1) + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }
}

void Explosion::updateFrame(int frame)
{
    if (current_animations == 3)
        delete this;
    else if (frame%2 == 0)
    {
        animate();
        current++;
    }
}

Explosion::~Explosion()
{
}
