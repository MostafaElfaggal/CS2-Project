#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QKeyEvent>

class Player : public Character
{
    Q_OBJECT
private:
    int toMove;
    QVector<QPixmap> as[4];
public:
    Player(int x_pos, int y_pos);

    void keyPressEvent(QKeyEvent *event);
    void increaseHealth(int h);
    void decreaseHealth(int h);
    void update(int frame);

    ~Player();


signals:
    void callSwitchView(int);
    void changeHealth(float);

// keyboard control slot
};

#endif // PLAYER_H
