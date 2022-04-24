#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "door.h"

#include <QTimer>

class Game : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int currentRoom;
    QVector<GameObject*> rooms[3];
    int PXstart[3], PYstart[3], PXend[3], PYend[3];
    Door* doors[3][3];

    Player p;
    QVector<Enemy*> enemys[3];
    int enemysPerRoom[3];

    int frame;
    QTimer* timer;

    QGraphicsView* view;

public:
    Game(QGraphicsView* v);
    void init();
    void loadRoom(int room, int boarddata[20][20], int offsetX, int offsetY);
    ~Game();
public slots:
    void run();
    void switchRoom(int newRoom);
    void decrementEnemy();
};
#endif // GAME_H
