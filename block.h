#ifndef BLOCK_H
#define BLOCK_H

#include "gameobject.h"

class Block : public GameObject
{
public:
    Block(int x_pos, int y_pos);
    void update(int frame);
};

#endif // BLOCK_H
