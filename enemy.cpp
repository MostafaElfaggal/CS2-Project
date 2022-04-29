#include "enemy.h"

Enemy::Enemy(int x_pos, int y_pos, QString img_file, int health, int power, int speed, int r) : Character(x_pos, y_pos, 50, 50, img_file, health, power, speed, false, LEFT, 2, r) // values to be changed
{
}

void Enemy::update(int frame){
    Character::update(frame);
}

Enemy::~Enemy()
{
}
