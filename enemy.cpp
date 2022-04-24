#include "enemy.h"

Enemy::Enemy(int x_pos, int y_pos, QString img_file) : Character(x_pos, y_pos, 50, 50, img_file, 100, 10, 25, false, LEFT, 2) // values to be changed
{
//    qDebug() << x_pos << y_pos;
}

void Enemy::update(int frame){
    Character::update(frame);
}

void Enemy::setPtrs(QVector<Enemy*>* s, int i)
{
    self = s;
    id = i;
}

Enemy::~Enemy()
{
    (*self)[id] = NULL;
}
