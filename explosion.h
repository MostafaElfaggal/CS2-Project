#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

class Explosion : public GameObject
{
private:
    int current;
    QVector<QPixmap> as;
public:
    Explosion(float x_pos, float y_pos);
    void update(int frame);
    ~Explosion();
};

#endif // EXPLOSION_H
