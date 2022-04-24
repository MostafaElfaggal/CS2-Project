#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
private:
    QVector<Enemy*>* self;
    int id;
public:
    Enemy(int x_pos, int y_pos, QString img_file);
    virtual void update(int frame);

    void setPtrs(QVector<Enemy*>* s, int i);

    ~Enemy();

// random control (might be through update)
};

#endif // ENEMY_H
