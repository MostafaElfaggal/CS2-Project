#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsView>

#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "explosion.h"
#include "door.h"
#include "healthpot.h"

#include "clickableimage.h"
#include "bar.h"
#include "shieldicon.h"
#include "winlose_status.h"

#include <QTimer>

const int ROOM_COUNT = 4, BOARD_SIZE_W = 23, BOARD_SIZE_H = 23;
const int offsetX = 75, offsetY = 100;

const long long MAX_FRAME = 1000000;

class Game : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int boarddata[BOARD_SIZE_H][BOARD_SIZE_W];

    int currentRoom;
    QVector<GameObject*> rooms[ROOM_COUNT];
    int Pstart[2];
    int Ploc[2];
    Door* doors[ROOM_COUNT][ROOM_COUNT];

    Player* p;
    Boss* boss;
    int enemysPerRoom[ROOM_COUNT];

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    bool isMusicRunning;

    bool running;
    QTimer* timer;

    WinLose_Status status;
    bool boss_died;

    ClickableImage pauseButton;
    bar HealthBar;
    ShieldIcon shield_icon;

    QGraphicsView* view;
    float viewOffset[2];
    QGraphicsPixmapItem bg;

    int room(int x_pos, int y_pos);
    int adjust_to_borders(int i, int di);

public:
    static int frame;

    Game(QGraphicsView* v);
    void init();
    void loadWorld();

    void shortestPath();

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
    void handleBossDeath();
    void playerHealthChanged(float);

signals:
    void showPauseMenu(float , float);
    void hidePauseMenu();
    void updatePlayerHealth(float);
};
#endif // GAME_H
