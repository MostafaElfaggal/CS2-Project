#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
public:
    Enemy(int x_pos, int y_pos, QString img_file);
    virtual void update(int frame);

// random control (might be through update)
};

#endif // ENEMY_H
