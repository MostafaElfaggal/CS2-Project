#include "bullet.h"
#include <QList>
#include <QGraphicsScene>
#include <wall.h>
#include <enemy1.h>

Bullet::Bullet(GameObject* &self, int x_pos, int y_pos, int p, direction d) : GameObject(x_pos, y_pos-7.5, 100, 40, "Bullet.png")
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

    if (checkCollision() == true)     // collision
    {
        scene()->removeItem(this); // Bullet still in heap
        qDebug()<<"Bullet collided";
    }

}

bool Bullet::checkCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

     for (int i = 0, n = colliding_items.size(); i < n; ++i)
     {
         if (typeid(*(colliding_items[i])) == typeid(Wall))
         {
             return true;
         }
         else if (typeid(*(colliding_items[i])) == typeid(Enemy1))
         {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            return true;
         }
     }

     return false;
}

void Bullet::update(int frame)
{
    Move();
}
