#include "character.h"

Character::Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir) : GameObject(x_pos, y_pos, size_w, size_h, img_file)
{
    health = Health;
    power = Power;
    speed = Speed;
    walkthrough = Walkthrough;
    dir = Dir;
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

}
