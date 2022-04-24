#include "bullet.h"

#include "wall.h"
#include "door.h"
#include "character.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"

Bullet::Bullet(GameObject *&s, int x_pos, int y_pos, int p, direction d, bool isPlayer) : GameObject(x_pos, y_pos, 25, 25, "fireBall1.png")
{
    // define animations
    for (int i=0; i<4; i++)
    {
        a1.push_back(QPixmap("fireBall" + QString::number(i+1) + ".png"));
        a1[i] = a1[i].scaledToHeight(25);
        a1[i] = a1[i].scaledToWidth(25);
    }

    animations = &a1;

    speed = 10;
    power = p;
    dir = d;

    byPlayer = isPlayer;
    inCollision = false;
    isShooterAlive = true;

    float translation = boundingRect().height()/2;
    switch(d){
    case UP:
        setRotation(270);
        setPos(x()-translation, y());
        break;
    case DOWN:
        setRotation(90);
        setPos(x()+translation, y());
        break;
    case RIGHT:
        setPos(x(), y()-translation);
        break;
    case LEFT:
        setRotation(180);
        setPos(x(), y()+translation);
        break;
    }

    self = &s;
}

void Bullet::Move()
{
    switch (dir)
    {
    case 0:
        setPos(x(), y() - speed);
        break;
    case 1:
        setPos(x(), y() + speed);
        break;
    case 2:
        setPos(x() + speed, y());
        break;
    case 3:
        setPos(x() - speed, y());
        break;
    }
    //    if (!scene()->sceneRect().contains(boundingRect())) scene()->removeItem(this);
    // collision

    if (checkCollision() == true) // collision
    {
        delete this;

    }
}

bool Bullet::checkCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    Character* creature;

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Wall) || typeid(*(colliding_items[i])) == typeid(Door))
        {
            inCollision = true;
            return true;
        } else if (typeid(*(colliding_items[i])) == typeid(Enemy1) || typeid(*(colliding_items[i])) == typeid(Enemy2))
        {
            inCollision = true;
            creature = qgraphicsitem_cast<Character*>(colliding_items[i]);
            if (creature && byPlayer)
                    creature->decreaseHealth(power);
            return true;

        } else if (typeid(*(colliding_items[i])) == typeid(Player))
        {
            inCollision = true;
            creature = qgraphicsitem_cast<Character*>(colliding_items[i]);
            if (creature && !byPlayer)
                creature->decreaseHealth(power);
            return true;

        }
    }

    return false;
}

void Bullet::update(int frame)
{
    if (frame%2 == 0) {
        animate(); // use the animate function every second which will auto scroll through the different animations
    }

    Move();
}

Bullet::~Bullet()
{
    scene()->removeItem(this);
    if (isShooterAlive)
        *self = NULL;
}
