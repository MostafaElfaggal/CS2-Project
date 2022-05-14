#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
private:
public:
    Enemy(int x_pos, int y_pos, QString img_file, int health, int power, int speed, int r);
    virtual void updateFrame(long long frame);

    ~Enemy();

// random control
};

#endif // ENEMY_H
