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
    void updateFrame(int frame);
};

#endif // FLAME_H
