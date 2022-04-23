#include "player.h"
#include <wall.h>
#include "bullet.h"
<<<<<<< HEAD
=======
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsRectItem>
>>>>>>> 1223e0a977336c5e58be74f78f09a5f944c133b9

#include <QDebug>

Player::Player(int x_pos, int y_pos) : Character(x_pos, y_pos, 50, 50, "Tweety.png", 100, 10, 25, false, RIGHT, 5)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    toMove = 4;
}

void Player::keyPressEvent(QKeyEvent *event)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////// Collison
    collisionUp = false;
    collisionDown = false;
    collisionRight = false;
    collisionLeft = false;

    QGraphicsRectItem *CheckUp = new QGraphicsRectItem(x()+12.5,this->y()-20,25,5);
    scene()->addItem(CheckUp); // Visual representation of collision checks

    QGraphicsRectItem *CheckDown = new QGraphicsRectItem(x()+12.5,this->y()+60,25,5);
    scene()->addItem(CheckDown);

    QGraphicsRectItem *CheckRight = new QGraphicsRectItem(this->x()+25,y()+25,25,5);
    scene()->addItem(CheckRight);

    QGraphicsRectItem *CheckLeft = new QGraphicsRectItem(this->x()-12.5,y()+25,25,5);
    scene()->addItem(CheckLeft);

    QList<QGraphicsItem *> colliding_CheckUp = CheckUp->collidingItems();
    QList<QGraphicsItem *> colliding_CheckDown = CheckDown->collidingItems();
    QList<QGraphicsItem *> colliding_CheckRight = CheckRight->collidingItems();
    QList<QGraphicsItem *> colliding_CheckLeft = CheckLeft->collidingItems();


       for (int i = 0, n = colliding_CheckUp.size(); i < n; ++i)
       {
           if (typeid(*(colliding_CheckUp[i])) == typeid(Wall))
           {
               collisionUp = true;
               qDebug()<<"Collision Up";
           }
       }

       for (int i = 0, n = colliding_CheckDown.size(); i < n; ++i)
       {
           if (typeid(*(colliding_CheckDown[i])) == typeid(Wall))
           {
               collisionDown = true;

               qDebug()<<"Collision Down";
           }
       }

       for (int i = 0, n = colliding_CheckRight.size(); i < n; ++i)
       {
           if (typeid(*(colliding_CheckRight[i])) == typeid(Wall))
           {
               collisionRight = true;
               qDebug()<<"Collision Right";
           }
       }

       for (int i = 0, n = colliding_CheckLeft.size(); i < n; ++i)
       {
           if (typeid(*(colliding_CheckLeft[i])) == typeid(Wall))
           {
               collisionLeft = true;
               qDebug()<<"Collision Left";
           }
       }

       scene()->removeItem(CheckUp);
       scene()->removeItem(CheckDown);
       scene()->removeItem(CheckRight);
       scene()->removeItem(CheckLeft);

       delete CheckUp;
       delete CheckDown;
       delete CheckRight;
       delete CheckLeft;
///////////////////////////////////////////////////////////////////////////////////////////////////////////// Collison

    if (event->key()==Qt::Key_Left && !collisionLeft)
    {
        toMove = LEFT;
    }
    else if (event->key()==Qt::Key_Right && !collisionRight)
    {
        toMove = RIGHT;
    }
    else if (event->key()==Qt::Key_Up && !collisionUp)
    {
        toMove = UP;
    }
    else if (event->key()==Qt::Key_Down && !collisionDown)
    {
        toMove = DOWN;
    }
    else if (event->key()==Qt::Key_Space)
    {
        Shoot();
    }

}

void Player::update(int frame)
{
    if (frame%3 == 0) { // collision check
        if (toMove != 4)
            Move((direction)toMove);
        toMove = 4;
    }

    Character::update(frame);
}
