#ifndef WALL_H
#define WALL_H

#include "gameobject.h"

class Wall : public GameObject
{
private:
    QVector<QPixmap> a1;
public:
    int value;

    Wall(int x_pos, int y_pos, int v);
    void updateFrame(int frame);
    ~Wall();
};

#endif // WALL_H
