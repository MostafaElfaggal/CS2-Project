#include "player.h"

#include "bullet.h"
#include <QGraphicsScene>

#include <QDebug>

Player::Player(int x_pos, int y_pos, GameObject* &B1, GameObject* &B2) : Character(x_pos, y_pos, 50, 50, "Tweety.png", 100, 10, 25, false, RIGHT)
{
    b1 = &B1;
    b2 = &B2;
    toMove = 0;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
    {
        toMove = 4;
    }
    else if (event->key()==Qt::Key_Right)
    {
        toMove = 3;
    }
    else if (event->key()==Qt::Key_Up)
    {
        toMove = 1;
    }
    else if (event->key()==Qt::Key_Down)
    {
        toMove = 2;
    }
    else if (event->key()==Qt::Key_Space)
    {
        if (*b1 == NULL)
        {
            *b1 = new Bullet(*b1, x()+25, y()+25, Power(), Dir());
            scene()->addItem(*b1);
        }
        else if (*b2 == NULL)
        {
            *b2 = new Bullet(*b2, x()+25, y()+25, Power(), Dir());
            scene()->addItem(*b2);
        }
    }
}

void Player::update(int frame)
{
    if (frame%3 == 0) { // collision check
        switch(toMove)
        {
        case 0:
            break;
        case 1:
            setPos(x(),y()-Speed());
            setDir(UP);
            break;
        case 2:
            setPos(x(),y()+Speed());
            setDir(DOWN);
            break;
        case 3:
            setPos(x()+Speed(),y());
            setDir(RIGHT);
            break;
        case 4:
            setPos(x()-Speed(),y());
            setDir(LEFT);
            break;
        }
        toMove = 0;
    }
}
