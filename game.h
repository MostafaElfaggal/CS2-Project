#ifndef GAME_H
#define GAME_H

#include "gameobject.h"

class Game : public GameObject
{
private:
    GameObject** objs;
    int objsSize;

public:
    Game(GameObject *items[], int n);
    ~Game();
public slots:
    void update();
};
#endif // GAME_H
