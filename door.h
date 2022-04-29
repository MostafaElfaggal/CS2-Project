#ifndef DOOR_H
#define DOOR_H

#include "gameobject.h"
#include "block.h"

class Door : public GameObject
{
private:
    QVector<QPixmap> as;
    int current;
    Block bg;
public:
    int from, to;
    bool open;

    Door(int x_pos, int y_pos, int f, int t);
    void init();

    void update(int frame);

    void unlock();
    ~Door();
};

#endif // DOOR_H
