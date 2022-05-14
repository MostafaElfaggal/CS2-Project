#ifndef ENEMY2_H
#define ENEMY2_H

#include "enemy.h"

class Enemy2 : public Enemy
{
private:
    QVector<QPixmap> as[4];
public:
    Enemy2(int x_pos, int y_pos, int r, QString enemyImg, int imgFrames);
    void updateFrame(long long frame);
};

#endif // ENEMY2_H
