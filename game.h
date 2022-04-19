#ifndef GAME_H
#define GAME_H

#include <QVector>
#include "gameobject.h"
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
private:
    QVector<GameObject*>* objs;
    int frame;

public:
    Game(QVector<GameObject*>* items);
    ~Game();
public slots:
    void run();
};
#endif // GAME_H
