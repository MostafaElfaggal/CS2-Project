#include "player.h"
#include "wall.h"
#include "bullet.h"

#include <QDebug>

Player::Player(int x_pos, int y_pos) : Character(x_pos, y_pos, 50, 50, "Player1.png", 100, 10, 25, false, RIGHT, 2)
{
    for (int i=0; i<9; i++)
    {
        a1.push_back(QPixmap("Player" + QString::number(i+1) + ".png"));
        a1[i] = a1[i].scaledToHeight(50);
        a1[i] = a1[i].scaledToWidth(50);
    }

    animations = &a1;

    setFlag(QGraphicsItem::ItemIsFocusable);
    toMove = 4;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    int check = -1;
    if (event->key() == Qt::Key_Up)
    {
        check = checkStep(UP);
        toMove = UP;
        setDir((direction)toMove);
    }
    else if (event->key() == Qt::Key_Down)
    {
        check = checkStep(DOWN);
        toMove = DOWN;
        setDir((direction)toMove);
    }
    else if (event->key() == Qt::Key_Right)
    {
        check = checkStep(RIGHT);
        toMove = RIGHT;
        setDir((direction)toMove);
    }
    else if (event->key() == Qt::Key_Left)
    {
        check = checkStep(LEFT);
        toMove = LEFT;
        setDir((direction)toMove);
    }
    else if (event->key() == Qt::Key_Space)
    {
        Shoot(true);
        return;
    }

    if (check < 0)
        toMove = 4;
    else if (check > 0)
    {
        toMove = 4;
        callSwitchView(check-1);
    }
}

void Player::update(int frame)
{
    if (frame%2 == 0)
        animate();
    if (frame % 3 == 0)
    {
        if (toMove != 4)
            Move((direction)toMove);
        toMove = 4;
    }

    Character::update(frame);
}

Player::~Player()
{
}

