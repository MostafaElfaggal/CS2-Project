#ifndef DOOR_H
#define DOOR_H

#include "gameobject.h"

class Door : public GameObject
{
public:
    Door(int x_pos, int y_pos, int f, int t);
    int from, to;
};

#endif // DOOR_H
