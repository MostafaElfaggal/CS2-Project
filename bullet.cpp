#include "bullet.h"

Bullet::Bullet(GameObject* &self, int x_pos, int y_pos, int p, direction d) : GameObject(x_pos, y_pos-7.5, 25, 15, "Bullet.png")
{
    speed = 10;
    power = p;
    dir = d;
}

void Bullet::Move()
{
    switch(dir) {
    case 0:
        setPos(x(), y()-speed);
        break;
    case 1:
        setPos(x(), y()+speed);
        break;
    case 2:
        setPos(x()+speed, y());
        break;
    case 3:
        setPos(x()-speed, y());
        break;
    }
//    if (!scene()->sceneRect().contains(boundingRect())) scene()->removeItem(this);
    // collision
}

void Bullet::update(int frame)
{
    Move();
}
