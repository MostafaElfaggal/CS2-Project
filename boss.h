#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

class Boss : public Enemy
{
private:
    QVector<QPixmap> as;
public:
    Boss(float x_pos, float y_pos, int r);
    void updateFrame(int frame);
};

#endif // BOSS_H
