#ifndef SHIELD_H
#define SHIELD_H

#include "gameitem.h"

class Shield : public GameItem
{
private:
    Shield** self;
public:
    Shield(float x_pos, float y_pos);
    void setLoc(float x_pos, float y_pos);
    void setPtrs(Shield** s);
    void updateFrame(long long frame);
    ~Shield();
};

#endif // SHIELD_H
