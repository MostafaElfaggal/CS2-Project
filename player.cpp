#include "player.h"
#include <wall.h>
#include "bullet.h"
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsRectItem>

#include <QDebug>

Player::Player(int x_pos, int y_pos) : Character(x_pos, y_pos, 50, 50, "Tweety.png", 100, 10, 25, false, RIGHT, 2)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    toMove = 4;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left && !checkStep(LEFT))
    {
        toMove = LEFT;
    }
    else if (event->key() == Qt::Key_Right && !checkStep(RIGHT))
    {
        toMove = RIGHT;
    }
    else if (event->key() == Qt::Key_Up && !checkStep(UP))
    {
        toMove = UP;
    }
    else if (event->key() == Qt::Key_Down && !checkStep(DOWN))
    {
        toMove = DOWN;
    }
    else if (event->key() == Qt::Key_Space)
    {
        Shoot();
    }
}

void Player::update(int frame)
{
    if (frame % 3 == 0)
    {
        if (toMove != 4)
            Move((direction)toMove);
        toMove = 4;
    }

    Character::update(frame);
}
