#include "game.h"

#include <QTimer>

Game::Game(QObject items[], int n)
{
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    timer->start(33);
}

