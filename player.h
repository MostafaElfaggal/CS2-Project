#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QKeyEvent>

class Player : public Character
{
    Q_OBJECT
private:
    int toMove;
public:
    Player(int x_pos, int y_pos);
    void keyPressEvent(QKeyEvent *event);
    void update(int frame);

signals:
    void callSwitchView(int);

// keyboard control slot (needs to integrate through update)
};

#endif // PLAYER_H
