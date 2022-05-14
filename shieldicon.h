#ifndef SHIELDICON_H
#define SHIELDICON_H

#include "gameobject.h"

class ShieldIcon : public GameObject
{
private:
    bool isVisible;
    bool running;
    int flickerCount;
//    float value;
//    QGraphicsEllipseItem prog;
public:
    ShieldIcon(float x_pos, float y_pos);
    void updateFrame(long long frame);
    void start();
    void flicker();
};

#endif // SHIELDICON_H
