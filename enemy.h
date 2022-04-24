#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
    Q_OBJECT
private:
    Enemy** self;
public:
    Enemy(int x_pos, int y_pos, QString img_file);
    virtual void update(int frame);

    void setPtrs(Enemy** s);

    ~Enemy();
signals:
    void die();

// random control (might be through update)
};

#endif // ENEMY_H
