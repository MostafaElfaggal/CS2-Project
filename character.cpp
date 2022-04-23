#include "character.h"

#include <QGraphicsScene>

Character::Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir, int maxBullets) : GameObject(x_pos, y_pos, size_w, size_h, img_file), MaxBullets(maxBullets)
{
    health = Health;
    Maxhealth = Health;
    power = Power;
    speed = Speed;
    walkthrough = Walkthrough;
    dir = Dir;

    QBrush greenbrush(Qt::green);
    QBrush blackbrush(Qt::black);
    QRect inner(x()+1,y()-15,GetHealth(),5);
    QRect outter(x(),y()-16,size_w,7);
    Health_bar.setBrush(greenbrush);
    Border_Health_bar.setBrush(blackbrush);
    Health_bar.setRect(inner);
    Border_Health_bar.setRect(outter);

    scene()->addItem(&Health_bar);
    scene()->addItem(&Border_Health_bar);


    bullets = new GameObject* [MaxBullets];
    for (int i=0; i<MaxBullets; i++) {
        *(bullets+i) = NULL;
    }
}

void Character::update(int frame)
{
    for (int i=0; i<MaxBullets; i++) {
        if (bullets[i] != NULL)
            bullets[i]->update(frame);
    }
    Health_bar.setPos(x()+1,y()-15);
    Border_Health_bar.setPos(x(),y()-16);
}

int Character::Health()
{
    return health;
}

int Character::GetHealth()
{
      return (health/(Maxhealth*1.0))*(boundingRect().width()-2);
//    health=100;
//    QBrush greenbrush(Qt::green);
//    QPen blackpen(Qt::black);
//    QGraphicsRectItem *green_bar;
//    QGraphicsRectItem *black_bar;
//    float w = boundingRect().width(), h=boundingRect().height();
//    switch(d){
//            case UP:
//                green_bar = new QGraphicsRectItem(x() + w/4, y() - 5, w/2, 5);
//                black_bar = new QGraphicsRectItem(x() + w/4, y() - 5, 50, 25);
//                break;
//            case DOWN:
//                green_bar = new QGraphicsRectItem(x() + w/4, y() + h, w/2, 5);
//                black_bar = new QGraphicsRectItem(x() - 5, y() + h/4, 50, 25);
//                break;
//            case RIGHT:
//                green_bar = new QGraphicsRectItem(x() + w, y() + h/4, 5, h/2);
//                black_bar = new QGraphicsRectItem(x() - 5, y() + h/4, 50, 25);
//                break;
//            case LEFT:
//                green_bar = new QGraphicsRectItem(x() - 5, y() + h/4, 5, h/2);
//                black_bar = new QGraphicsRectItem(x() - 5, y() + h/4, 50, 25);
//                break;
//            }
//     scene()->addItem(green_bar);
//     scene()->addItem(black_bar);





//    delete green_bar;
//    delete black_bar;
//    return health;
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

int Character::checkStep(direction d)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////// Collison

    float w = boundingRect().width(), h=boundingRect().height();
    Door* doorptr;

    int collision = 0;
    QGraphicsRectItem *Check;

    switch(d){
    case UP:
        Check = new QGraphicsRectItem(x() + w/4, y() - 5, w/2, 5);
        break;
    case DOWN:
        Check = new QGraphicsRectItem(x() + w/4, y() + h, w/2, 5);
        break;
    case RIGHT:
        Check = new QGraphicsRectItem(x() + w, y() + h/4, 5, h/2);
        break;
    case LEFT:
        Check = new QGraphicsRectItem(x() - 5, y() + h/4, 5, h/2);
        break;
    }
    scene()->addItem(Check);
    QList<QGraphicsItem *> colliding_Check = Check->collidingItems();

    for (int i = 0, n = colliding_Check.size(); i < n; ++i)
    {
        if (typeid(*(colliding_Check[i])) == typeid(Wall))
            collision = -1;
        else if (typeid(*(colliding_Check[i])) == typeid(Door))
        {
            doorptr = qgraphicsitem_cast<Door*>(colliding_Check[i]);
            if (doorptr)
                collision = doorptr->to + 1; // room number from 1 to 3
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
    int i = 0;
    while (bullets[i] != NULL && i<MaxBullets)
        i++;
    if (bullets[i] == NULL && i<MaxBullets)
    {
        float w = boundingRect().width(), h=boundingRect().height();
        switch(dir){
        case UP:
            bullets[i] = new Bullet(bullets[i], x()+w/2, y(), Power(), Dir(), isPlayer);
            break;
        case DOWN:
            bullets[i] = new Bullet(bullets[i], x()+w/2, y()+h, Power(), Dir(), isPlayer);
            break;
        case RIGHT:
            bullets[i] = new Bullet(bullets[i], x()+w, y()+h/2, Power(), Dir(), isPlayer);
            break;
        case LEFT:
            bullets[i] = new Bullet(bullets[i], x(), y()+h/2, Power(), Dir(), isPlayer);
            break;
        }
        scene()->addItem(bullets[i]);
    }
}

void Character::increaseHealth(int h)
{
    health += h;
}

void Character::decreaseHealth(int h)
{
    health -= h;
    qDebug() << "decreased health by " << h;
}
