#ifndef FLAME_H
#define FLAME_H

#include "gameitem.h"

class Flame : public GameItem
{
private:
    int current;
    QVector<QPixmap> as[3];
public:
    Flame(float x_pos, float y_pos);
    void updateFrame(long long frame);
};

#endif // FLAME_H
