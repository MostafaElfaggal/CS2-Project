#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameitem.h"

class Explosion : public GameItem
{
private:
    int current;
public:
    Explosion(float x_pos, float y_pos);
    void updateFrame(int frame);
    ~Explosion();
};

#endif // EXPLOSION_H
