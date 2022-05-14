#include "block.h"

Block::Block(int x_pos, int y_pos) : GameObject(x_pos, y_pos, 50, 50, "Road.png", "block")
{
    setZValue(1);
}

void Block::updateFrame(long long frame){}
