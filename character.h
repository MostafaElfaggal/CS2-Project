#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobject.h"
#include "bullet.h"

class Character : public GameObject
{
private:
    int health;
    int power;
    int speed;
    bool walkthrough;
    direction dir;

    const int MaxBullets;
    GameObject **bullets;

public:
    Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir, int maxBullets);

    virtual void update(int frame); // virtual to be discussed

    int Health();
    int Power();
    int Speed();
    bool Walkthrough();
    direction Dir();
    void setDir(direction d);

    bool checkStep(int x, int y); // checks if there is collision at x and y location
    void Move(direction d); // moves speed pixels in the direction of dir (checks for obstackle collision if walkthrough is false using checkStep function)

    void Shoot(); // shoots a bullet in the direction of dir
    void increaseHealth(int h);
    void decreaseHealth(int h);
};

#endif // CHARACTER_H
