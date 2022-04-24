#ifndef DOOR_H
#define DOOR_H

#include "gameobject.h"

class Door : public GameObject
{
public:
    Door(int x_pos, int y_pos, int f, int t, bool isOpen=false);
    int from, to;
    bool open;

    void unlock();
};

#endif // DOOR_H
