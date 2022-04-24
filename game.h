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

const int ROOM_COUNT = 4;

class Game : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int currentRoom;
    QVector<GameObject*> rooms[ROOM_COUNT];
    int PXstart[ROOM_COUNT], PYstart[ROOM_COUNT], PXend[ROOM_COUNT], PYend[ROOM_COUNT];
    Door* doors[ROOM_COUNT][ROOM_COUNT];

    Player p;
    QVector<Enemy*> enemys[ROOM_COUNT];
    int enemysPerRoom[ROOM_COUNT];

    int frame;
    bool running;
    QTimer* timer;

    QGraphicsView* view;

public:
    Game(QGraphicsView* v);
    void init();
    void loadRoom(int room, int boarddata[20][20], int offsetX, int offsetY);
    ~Game();
public slots:
    void start();
    void run();
    void switchRoom(int newRoom);
    void decrementEnemy();
};
#endif // GAME_H
