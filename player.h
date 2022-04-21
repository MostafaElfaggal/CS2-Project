#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QKeyEvent>

class Player : public Character
{
private:
    GameObject **b1, **b2;
    int toMove;
public:
    Player(int x_pos, int y_pos, GameObject* &B1, GameObject* &B2);
    void keyPressEvent(QKeyEvent *event);
    void update(int frame);

// keyboard control slot (needs to integrate through update)
};

#endif // PLAYER_H
