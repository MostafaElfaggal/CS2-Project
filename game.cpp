#include "game.h"

#include <QTimer>

Game::Game(GameObject *items[], int n)
{
    objsSize = n;
    objs = new GameObject*[n];
    for(int i=0; i<n; i++) {
        objs[i] = items[i];
    }

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    timer->start(33);
}

void Game::update() {
    for (int i=0; i<objsSize; i++) {
        objs[i]->update();
    }
}

Game::~Game() {
    for (int i=0; i<objsSize; i++) {
        delete objs[i];
    }
}
