#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"


class Bullet : public GameObject
{
private:
    int speed;
    int power;
    direction dir;
public:
    Bullet(GameObject* &self, int x_pos, int y_pos, int p, direction d);
    void Move(); // moves speed pixels in the direction dir, after movement checks for collision
    bool checkCollision(); // checks for collision on other objects and returns bool
    void update(int frame);
};

#endif // BULLET_H
