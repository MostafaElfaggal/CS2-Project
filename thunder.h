#ifndef THUNDER_H
#define THUNDER_H

#include "gameitem.h"
#include "flame.h"

class Thunder : public GameItem
{
public:
    Thunder(float x_pos, float y_pos);
    void updateFrame(long long frame);
    ~Thunder();
};

#endif // THUNDER_H
