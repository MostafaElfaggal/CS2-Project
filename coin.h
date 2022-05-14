#ifndef COIN_H
#define COIN_H

#include "gameitem.h"

class Coin : public GameItem
{
public:
    Coin(float x_pos, float y_pos);
    void update(long long frame);
};

#endif // COIN_H
