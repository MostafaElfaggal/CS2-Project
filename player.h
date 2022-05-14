#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "shield.h"
#include "shieldicon.h"
#include <QKeyEvent>

class Player : public Character
{
    Q_OBJECT
private:
    int toMove;
    QVector<QPixmap> as[4];

    bool isShieldOn;

    Shield* shield;
    ShieldIcon* shield_icon;
public:
    Player(int x_pos, int y_pos);

    void setPtrs(ShieldIcon* si);

    void keyPressEvent(QKeyEvent *event);
    void Move(direction d);
    void increaseHealth(int h);
    void decreaseHealth(int h);
    void updateFrame(long long frame);

    ~Player();


signals:
    void callSwitchView(int);
    void changeHealth(float);

    void changePurse(int);

// keyboard control slot
};

#endif // PLAYER_H
