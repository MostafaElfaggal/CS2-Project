#include "explosion.h"

Explosion::Explosion(float x_pos, float y_pos) : GameObject(x_pos, y_pos, 50, 50, "Explosion_1.png", "explosion")
{
    current = 1;
    for (int i=0; i<4; i++)
    {
        as.push_back(QPixmap("Explosion_" + QString::number(i+1) + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }

    animations = &as;
    setZValue(80);
}

void Explosion::update(int frame)
{
    if (current == 4)
        delete this;
    else if (frame%2 == 0)
    {
        animate();
        current++;
    }
}

Explosion::~Explosion()
{
    scene()->removeItem(this);
}
