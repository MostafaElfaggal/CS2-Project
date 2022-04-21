#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QKeyEvent>

class Player : public Character
{
public:
    Player(int x_pos, int y_pos);
    void keyPressEvent(QKeyEvent *event);

// keyboard control slot (needs to integrate through update)
};

#endif // PLAYER_H
