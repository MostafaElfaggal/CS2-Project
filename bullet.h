#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"


class Bullet : public GameObject
{
    Q_OBJECT
private:
    QVector<QPixmap> a1;

    int speed;
    int power;
    direction dir;

    bool byPlayer;

    GameObject** self;
public:
    bool inCollision;
    bool isShooterAlive;

    Bullet(int x_pos, int y_pos, int p, direction d, bool isPlayer);
    void Move(); // moves speed pixels in the direction dir, after movement checks for collision
    bool checkCollision(); // checks for collision on other objects and returns bool
    void updateFrame(int frame);
    ~Bullet();

public slots:
    void deleteBullet(bool isShooterDying);

signals:
    void removeBullet();
};

#endif // BULLET_H
