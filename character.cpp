#include "character.h"

#include <QGraphicsScene>

Character::Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir, int maxBullets) : GameObject(x_pos, y_pos, size_w, size_h, img_file), MaxBullets(maxBullets)
{
    health = Health;
    power = Power;
    speed = Speed;
    walkthrough = Walkthrough;
    dir = Dir;

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
}

int Character::Health()
{
    return health;
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

bool Character::checkStep(int x, int y)
{
    return x+y;
}

void Character::Move(direction d)
{
    switch(d)
    {
    case UP:
        setPos(x(),y()-Speed());
        setDir(UP);
        break;
    case DOWN:
        setPos(x(),y()+Speed());
        setDir(DOWN);
        break;
    case RIGHT:
        setPos(x()+Speed(),y());
        setDir(RIGHT);
        break;
    case LEFT:
        setPos(x()-Speed(),y());
        setDir(LEFT);
        break;
    }
}

void Character::Shoot()
{
    int i = 0;
    while (bullets[i] != NULL && i<MaxBullets)
        i++;
    if (bullets[i] == NULL)
    {
        bullets[i] = new Bullet(bullets[i], x()+50, y()+25, Power(), Dir());
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
}
