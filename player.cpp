#include "player.h"

Player::Player(int x_pos, int y_pos) : Character(x_pos, y_pos, 50, 50, "Tweety.png")
{

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
    {
        setPos(x()-50,y());
    }
    else if (event->key()==Qt::Key_Right)
    {
        setPos(x()+50,y());
    }
    else if (event->key()==Qt::Key_Up)
    {
        setPos(x(),y()-50);
    }
    else if (event->key()==Qt::Key_Down)
    {
        setPos(x(),y()+50);
    }
}
