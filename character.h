#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobject.h"
#include "bullet.h"
#include "explosion.h"

#include "wall.h"
#include "block.h"
#include "door.h"
#include "gameitem.h"

#include "rectangle.h"

class Character : public GameObject
{
    Q_OBJECT
private:
    int MyRoom;

    int power;
    int speed;
    bool walkthrough;

    bool canShoot;

    bool toBeDeleted;

    Rectangle Health_bar;
    Rectangle Border_Health_bar;

    const int MaxBullets;
    int BulletsCount;
//    GameObject **bullets;

protected:
    bool isPlayer;

public:
    int health;
    int Maxhealth;
    direction dir;

    bool isExplode;

    Character(int x_pos, int y_pos, int size_w, int size_h, QString img_file, int Health, int Power, int Speed, bool Walkthrough, direction Dir, int maxBullets, int r);
    void init();

    virtual void updateFrame(long long frame); // virtual to be discussed

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
    void blockBullets();
    virtual void increaseHealth(int h);
    virtual void decreaseHealth(int h);

    ~Character();

public slots:
    void decrementBullets();

signals:
    void ClearBullets(bool);
    void die(int);
};

#endif // CHARACTER_H
