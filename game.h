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
#include "explosion.h"
#include "door.h"

#include "clickableimage.h"
#include "bar.h"
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
    int Pstart[2];
    Door* doors[ROOM_COUNT][ROOM_COUNT];

    Player* p;
    int enemysPerRoom[ROOM_COUNT];

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    bool isMusicRunning;

    int frame;
    bool running;
    QTimer* timer;

    WinLose_Status status;

    ClickableImage pauseButton;
    bar HealthBar;

    QGraphicsView* view;
    float viewOffset[2];

    int room(int x_pos, int y_pos);

public:
    Game(QGraphicsView* v);
    void init();
    void loadWorld();
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
    void decrementEnemy(int);
    void playerHealthChanged(float);

signals:
    void showPauseMenu(float , float);
    void hidePauseMenu();
    void updatePlayerHealth(float);
};
#endif // GAME_H
