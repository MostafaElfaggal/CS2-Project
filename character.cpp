#include "character.h"

#include <QGraphicsScene>

Character::Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir, int maxBullets, int r) : GameObject(x_pos, y_pos, size_w, size_h, img_file, "character"), MaxBullets(maxBullets)
{
    MyRoom = r;

    health = Health;
    Maxhealth = Health;
    power = Power;
    speed = Speed;
    walkthrough = Walkthrough;
    dir = Dir;

    isExplode = true;

    BulletsCount = 0;
    canShoot = true;

    Health_bar.setBrush(QBrush(Qt::green));
    Border_Health_bar.setBrush(QBrush(Qt::black));

    Health_bar.setRect(QRect(0,0,GetHealth(),5));
    Health_bar.setPos(x()+1,y()-15);

    Border_Health_bar.setRect(QRect(0,0,size_w, 7));
    Border_Health_bar.setPos(x(),y()-16);
}

void Character::init(){
    scene()->addItem(&Border_Health_bar);
    scene()->addItem(&Health_bar);
    setZValue(4);
    Border_Health_bar.setZValue(5);
    Health_bar.setZValue(6);
}

void Character::update(int frame)
{
    float w = boundingRect().width();

    Health_bar.setRect(QRect(0,0,GetHealth(),5));
    Health_bar.setPos(x()+1,y()-15);

    Border_Health_bar.setRect(QRect(0,0,w, 7));
    Border_Health_bar.setPos(x(),y()-16);
}

int Character::Health()
{
    return health;
}

int Character::GetHealth()
{
      return (health/(Maxhealth*1.0))*(boundingRect().width()-2);
}

int Character::Power()
{
    return power;
}

int Character::Speed()
{
    return speed;
}

bool Character::Walkthrough()
{
    return walkthrough;
}

direction Character::Dir()
{
    return dir;
}

void Character::setDir(direction d)
{
    dir = d;
}

void Character::Hide()
{
    scene()->removeItem(&Health_bar);
    scene()->removeItem(&Border_Health_bar);
}

int Character::checkStep(direction d)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////// Collison

    float w = boundingRect().width(), h=boundingRect().height();
    Door* doorptr;
    Wall* wallptr;

    int collision = 0;
    QGraphicsRectItem *Check;

    switch(d){
    case UP:
        Check = new QGraphicsRectItem(x() + w/4, y() - 20, w/2, 20);
        break;
    case DOWN:
        Check = new QGraphicsRectItem(x() + w/4, y() + h, w/2, 20);
        break;
    case RIGHT:
        Check = new QGraphicsRectItem(x() + w, y() + h/4, 20, h/2);
        break;
    case LEFT:
        Check = new QGraphicsRectItem(x() - 20, y() + h/4, 20, h/2);
        break;
    }
    scene()->addItem(Check);
    QList<QGraphicsItem *> colliding_Check = Check->collidingItems();

    for (int i = 0, n = colliding_Check.size(); i < n; ++i)
    {
        if (typeid(*(colliding_Check[i])) == typeid(Wall))
        {
            wallptr = qgraphicsitem_cast<Wall*>(colliding_Check[i]);
            collision = wallptr->value;
            break;
        } else if (typeid(*(colliding_Check[i])) == typeid(Door))
        {
            doorptr = qgraphicsitem_cast<Door*>(colliding_Check[i]);
            if (doorptr)
            {
                if (!doorptr->open)
                    collision = 9;
                else
                    collision = (doorptr->from*10 + doorptr->to) + 1; // room number from and to (1 to 3) combined with 10*from+to
            }
        }
    }
    scene()->removeItem(Check);
    delete Check;
    return collision;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////// Collison
}

void Character::Move(direction d)
{
    switch(d)
    {
    case UP:
        setPos(x(),y()-Speed());
        break;
    case DOWN:
        setPos(x(),y()+Speed());
        break;
    case RIGHT:
        setPos(x()+Speed(),y());
        break;
    case LEFT:
        setPos(x()-Speed(),y());
        break;
    }
}

void Character::Shoot(bool isPlayer)
{
    if (!canShoot || BulletsCount >= MaxBullets)
        return;

    Bullet* b;
    float w = boundingRect().width(), h=boundingRect().height();
    switch(dir){
    case UP:
        b = new Bullet(x()+w/2, y(), Power(), Dir(), isPlayer);
        break;
    case DOWN:
        b = new Bullet(x()+w/2, y()+h, Power(), Dir(), isPlayer);
        break;
    case RIGHT:
        b = new Bullet(x()+w, y()+h/2, Power(), Dir(), isPlayer);
        break;
    case LEFT:
        b = new Bullet(x(), y()+h/2, Power(), Dir(), isPlayer);
        break;
    }

    scene()->addItem(b);
    connect(b, SIGNAL(removeBullet()), this, SLOT(decrementBullets()));
    connect(this, SIGNAL(ClearBullets()), b, SLOT(deleteBullet()));
    BulletsCount++;
}

void Character::blockBullets()
{
    canShoot = false;
}

void Character::increaseHealth(int h)
{
    if (health + h <= Maxhealth)
        health += h;
}

void Character::decreaseHealth(int h)
{
    health -= h;
    if (health <= 0)
        delete this;
}

Character::~Character()
{
    if (isExplode)
        scene()->addItem(new Explosion(x(), y()));
    scene()->removeItem(this);
    die(MyRoom);
}

void Character::decrementBullets()
{
    BulletsCount--;
}
