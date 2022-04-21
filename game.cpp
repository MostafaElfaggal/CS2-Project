#include "game.h"

#include <QDebug>

#include <QTimer>

Game::Game(QVector<GameObject*> *items)
{
    frame = 0;
    objs = items;

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));

    timer->start(33);
}

void Game::run() {
    frame++;
    frame %= 1000;
    for (int i=0; i<objs->size(); i++) {
        if ((*objs)[i] != NULL)
            (*objs)[i]->update(frame);
    }

//    qDebug() << "running...";
}

Game::~Game() {}
