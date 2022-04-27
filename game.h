#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QObject>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsView>

#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "door.h"

#include "clickableimage.h"
#include "winlose_status.h"

#include <QTimer>

const int ROOM_COUNT = 4, BOARD_SIZE_W = 23, BOARD_SIZE_H = 23;
const int offsetX = 75, offsetY = 100;

class Game : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int boarddata[BOARD_SIZE_H][BOARD_SIZE_W];

    int currentRoom;
    QVector<GameObject*> rooms[ROOM_COUNT];
    int PXstart[ROOM_COUNT], PYstart[ROOM_COUNT], PXend[ROOM_COUNT], PYend[ROOM_COUNT];
    Door* doors[ROOM_COUNT][ROOM_COUNT];

    Player* p;
    QVector<Enemy*> enemys[ROOM_COUNT];
    int enemysPerRoom[ROOM_COUNT];

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    bool isMusicRunning;

    int frame;
    bool running;
    QTimer* timer;

    WinLose_Status status;

    ClickableImage pauseButton;

    QGraphicsView* view;
    float viewOffset[2];

    int room(int x_pos, int y_pos);

public:
    Game(QGraphicsView* v);
    void init();
    void loadWorld();
    void loadRoom(int room, int boarddata[BOARD_SIZE_H][BOARD_SIZE_W], int offsetX, int offsetY);
    ~Game();
public slots:
    void start();
    void run();
    void pauseMenu();
    void pause();
    void resume();

    void musicOn();
    void musicOff();

    void Win();
    void Lose();

    void switchRoom(int newRoom);
    void decrementEnemy();
signals:
    void showPauseMenu(float , float);
    void hidePauseMenu();
};
#endif // GAME_H
