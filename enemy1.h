#ifndef ENEMY1_H
#define ENEMY1_H

#include "enemy.h"

class Enemy1 : public Enemy
{
private:
    QVector<QPixmap> as[4];
public:
    Enemy1(int x_pos, int y_pos, int r, QString enemyImg, int imgFrames, int x_loc, int y_loc);
    void updateFrame(long long frame);
};

#endif // ENEMY1_H
