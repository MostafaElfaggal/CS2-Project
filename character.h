#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobject.h"
#include "bullet.h"

#include "wall.h"
#include "block.h"
#include "door.h"

class Character : public GameObject
{
    Q_OBJECT
private:
    int health;
    int Maxhealth;
    int power;
    int speed;
    bool walkthrough;

    bool canShoot;

    QGraphicsRectItem Health_bar;
    QGraphicsRectItem Border_Health_bar;

    const int MaxBullets;
    GameObject **bullets;

public:
    direction dir;

    Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir, int maxBullets);
    void init();

    virtual void update(int frame); // virtual to be discussed

    int Health();
    int GetHealth();
    int Power();
    int Speed();
    bool Walkthrough();
    direction Dir();
    void setDir(direction d);

    void Hide();

    int checkStep(direction d); // checks if there is collision at x and y location
    void Move(direction d); // moves speed pixels in the direction of dir (checks for obstackle collision if walkthrough is false using checkStep function)

    void Shoot(bool isPlayer); // shoots a bullet in the direction of dir
    void ClearBullets(bool isShooterDying);
    void blockBullets();
    void increaseHealth(int h);
    void decreaseHealth(int h);

    ~Character();
signals:
    void die();
};

#endif // CHARACTER_H
