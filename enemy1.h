#ifndef ENEMY1_H
#define ENEMY1_H

#include "enemy.h"

class Enemy1 : public Enemy
{
private:
    QVector<QPixmap> a1;
public:
    Enemy1(int x_pos, int y_pos);
    void update(int frame);
};

#endif // ENEMY1_H
