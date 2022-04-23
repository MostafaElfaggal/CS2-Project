#ifndef GAME_H
#define GAME_H

#include <QVector>
#include "gameobject.h"
#include <QObject>
#include <QGraphicsRectItem>

#include "player.h"

#include <QTimer>

class Game : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QVector<GameObject*> rooms[3];
    QVector<GameObject*>* objs;
    int currentRoom;
    int frame;
    QTimer* timer;
    Player p;

public:
    Game();
    void init();
    ~Game();
public slots:
    void run();
};
#endif // GAME_H
