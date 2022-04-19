#ifndef GAME_H
#define GAME_H

#include "gameobject.h"
#include <QObject>

class Game : QObject
{
private:
    GameObject** objs;
    int objsSize;
    int frame;

public:
    Game(GameObject *items[], int n);
    ~Game();
public slots:
    void update();
};
#endif // GAME_H
