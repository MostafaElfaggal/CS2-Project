#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QKeyEvent>

class Player : public Character
{
    Q_OBJECT
private:
    int toMove;
    QVector<QPixmap> a1;
public:
    Player(int x_pos, int y_pos);

    void keyPressEvent(QKeyEvent *event);
    void update(int frame);

    ~Player();


signals:
    void callSwitchView(int);

// keyboard control slot (needs to integrate through update)
};

#endif // PLAYER_H
