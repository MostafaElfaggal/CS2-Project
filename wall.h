#ifndef WALL_H
#define WALL_H

#include "gameobject.h"

class Wall : public GameObject
{
public:
    Wall(int x_pos, int y_pos);
    void update(int frame);
    ~Wall();
};

#endif // WALL_H
