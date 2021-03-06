#include "player.h"
#include "wall.h"
#include "bullet.h"
#include "gameitem.h"

#include <QDebug>

Player::Player(int x_pos, int y_pos) : Character(x_pos, y_pos, 50, 50, "PlayerE_01.png", 100, 10, 50, false, RIGHT, 1000, 0)
{
    // define animations
    QString chars[4] = {"N", "S", "E", "W"};
    for (int _=0; _<4; _++)
    for (int i=0; i<3; i++)
    {
        as[_].push_back(QPixmap("Player" + chars[_] + "_" + QString::number(i+1).rightJustified(2, '0') + ".png"));
        as[_][i] = as[_][i].scaledToHeight(50);
        as[_][i] = as[_][i].scaledToWidth(50);
    }

    animations = &as[2];

    setFlag(QGraphicsItem::ItemIsFocusable);
    toMove = 4;

    isExplode = false;

    isPlayer = true;

    isShieldOn = false;
    shield = NULL;
}

void Player::setPtrs(ShieldIcon *si)
{
    shield_icon = si;
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

    if (check < 0 || check == 9)
        toMove = 4;
    else if (check >= 100)
    {
        check -= 100;
        if (check==PotHealth)
            increaseHealth(50);
        else if (check==ThunderStrike)
            decreaseHealth(30);
        else if (check==FlameWisp)
            decreaseHealth(5);
        else if (check==Shield_Totem)
        {
            isShieldOn = true;
            startTimer(210);
            shield_icon->start();
        }
    }
    else if (check > 0)
    {
        callSwitchView(check-1);
    }
}

void Player::Move(direction d)
{
    Character::Move(d);
    if (shield != NULL)
        shield->setLoc(x(), y());
}

void Player::increaseHealth(int h)
{
    changeHealth((health+h)*100/Maxhealth);
    Character::increaseHealth(h);
}

void Player::decreaseHealth(int h)
{
    if (!isShieldOn)
    {
        changeHealth((health-h)*100/Maxhealth);
        Character::decreaseHealth(h);
    } else if (shield == NULL)
    {
        shield = new Shield(x(), y());
        shield->setPtrs(&shield);
        scene()->addItem(shield);
    }
}


void Player::updateFrame(long long frame)
{
    int check = checkStep(NONE);
    if (check >= 100)
    {
        check -= 100;
        if (check==PotHealth)
            increaseHealth(50);
        else if (check==coin)
            changePurse(10);
        else if (check==ThunderStrike)
            decreaseHealth(30);
        else if (check==FlameWisp)
            decreaseHealth(5);
        else if (check==Shield_Totem && !isShieldOn)
        {
            isShieldOn = true;
            startTimer(210);
            shield_icon->start();
        }
    }

    if (frame % 3 == 0)
    {
        animations = &as[dir];
        if (toMove != 4)
        {
            Move((direction)toMove);
        }
        toMove = 4;
        animate();
    }

    if (frame%300 == 0)
        increaseHealth(5);


    Character::updateFrame(frame);
    GameObject::updateFrame(frame);

    if(isShieldOn && !timer)
    {
        isShieldOn = false;
//        qDebug() << "end";
    }
}

Player::~Player()
{
}

