#ifndef SHIELDTOTEM_H
#define SHIELDTOTEM_H

#include "gameitem.h"

class ShieldTotem : public GameItem
{
private:
    int current;
    QVector<QPixmap> as[3];
    bool dying;
public:
    ShieldTotem(float x_pos, float y_pos);
    void updateFrame(long long frame);
    void die();
    ~ShieldTotem();
};

#endif // SHIELDTOTEM_H
