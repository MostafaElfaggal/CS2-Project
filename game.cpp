#include "game.h"

#include <QDebug>
#include <QTimer>

#include <QFile>
#include <QTextStream>

#include "menu.h"

#include "block.h"
#include "wall.h"
#include "door.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"
#include "Button.h"

int Game::room(int x_pos, int y_pos)
{
    // 0 1
    // 3 2
    int res = 0;
    if (y_pos < 10)
    {
        if (x_pos < 10)
            res = 0;
        else
            res = 1;
    }
    else
    {
        if (x_pos < 10)
            res = 3;
        else
            res = 2;
    }

    return res;
}

Game::Game(QGraphicsView *v) : QGraphicsRectItem(QRect(0, 0, 1, 1)), pauseButton(25, 25, "pauseBtn.png", "pauseBtn-hover", "pauseBtn-pressed.png", 50, 50)
{
    p = new Player(0, 0);

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("song.mp3"));
    audioOutput->setVolume(50);

    view = v;
    viewOffset[0] = 0;
    viewOffset[1] = 0;

    frame = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    connect(p, SIGNAL(callSwitchView(int)), this, SLOT(switchRoom(int)));
}

void Game::init()
{
    //    int boarddata[ROOM_COUNT][BOARD_SIZE_H][BOARD_SIZE_W];

    enemysPerRoom[0] = 0;
    enemysPerRoom[1] = 0;
    enemysPerRoom[2] = 0;
    enemysPerRoom[3] = 0;

    //    for (int i=1; i<=ROOM_COUNT; i++)
    //        loadRoom(i, boarddata[i-1], 50+600*(i-1), 50);
    loadWorld();

    ///////////////////////////////////////////////////////////////////////////////////////// Enemys
    for (int _ = 0; _ < ROOM_COUNT; _++)
        for (int i = 0; i < enemys[_].size(); i++)
        {
            scene()->addItem(enemys[_][i]);
            enemys[_][i]->init();
            connect(enemys[_][i], SIGNAL(die()), this, SLOT(decrementEnemy()));
        }
    /////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    p->setPos(PXstart[0], PYstart[0]);
    scene()->addItem(p);
    p->init();
    connect(p, SIGNAL(die()), this, SLOT(Lose()));
    /////////////////////////////////////////////////////////////////////////////////////////

    scene()->addItem(&status);
    status.init();

    scene()->addItem(&pauseButton);
    connect(&pauseButton, SIGNAL(press()), this, SLOT(pauseMenu()));
    //    connect(&pauseButton,SIGNAL(resume()),this,SLOT(resume()));

    currentRoom = 0;
    running = false;
}

void Game::loadWorld()
{
    QString temp;
    int tmp;
    int to = 0;
    GameObject *background;

    QFile file("World.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:";
        qCritical() << file.errorString();
        return;
    }
    QTextStream stream(&file);

    for (int i = 0; i < BOARD_SIZE_H; i++)
    {

        for (int j = 0; j < BOARD_SIZE_W; j++)
        {
            stream >> temp;
            if (temp == "//")
                boarddata[i][j] = NULL;
            else if (temp == "st")
            { // starting point of the world
                boarddata[i][j] = 1;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;

                PXstart[0] = offsetX + 50 * j;
                PYstart[0] = offsetY + 50 * i;
            }
            else if (temp == "e1")
            { // enemy1
                boarddata[i][j] = 1;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;

                Enemy *tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i);
                enemys[room(j, i)].push_back(tmp);
                tmp->setPtrs(&enemys[room(j, i)], enemys[room(j, i)].size() - 1);
                enemysPerRoom[room(j, i)]++;
            }
            else if (temp == "e2")
            {
                boarddata[i][j] = 1;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;
                Enemy *tmp = new Enemy2(offsetX + 50 * j, offsetY + 50 * i);
                enemys[room(j, i)].push_back(tmp);
                tmp->setPtrs(&enemys[room(j, i)], enemys[room(j, i)].size() - 1);
                enemysPerRoom[room(j, i)]++;
            }
            else if (temp == "d1" || temp == "d2" || temp == "d3" || temp == "d4")
            { // doors
                //                 boarddata[i][j]=-3;
                //                 boarddata[2*i+1][2*j]=-3;
                //                 boarddata[2*i][2*j+1]=-3;
                //                 boarddata[2*i+1][2*j+1]=-3;
                if (temp == "d1")
                    to = 0;
                else if (temp == "d2")
                    to = 1;
                else if (temp == "d3")
                    to = 2;
                else if (temp == "d4")
                    to = 3;
                boarddata[i][j] = -1 * (to + 3);
            }
            else
            {
                tmp = temp.toInt();
                boarddata[i][j] = tmp;
                //                 boarddata[2*i+1][2*j]=tmp;
                //                 boarddata[2*i][2*j+1]=tmp;
                //                 boarddata[2*i+1][2*j+1]=tmp;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE_H; i++)
    {
        for (int j = 0; j < BOARD_SIZE_W; j++)
        {
            if (boarddata[i][j] == NULL)
                continue;
            else if (boarddata[i][j] <= -3)
            {

                to = -1 * (boarddata[i][j]) - 3;
                doors[room(j, i)][to] = new Door(offsetX + 50 * j, offsetY + 50 * i, room(j, i), to);
                background = doors[room(j, i)][to];
                boarddata[i][j] = -3;
            }
            else if (boarddata[i][j] < 0)
            {
                background = new Wall(offsetX + 50 * j, offsetY + 50 * i, boarddata[i][j]);
                QString vertical = "N", horizontal = "N";
                if (boarddata[i][j] == -2)
                {
                    if (i == 0 || i==13 || boarddata[i-1][j] == NULL)
                        vertical = "T";
                    else if (i == BOARD_SIZE_H - 1 || i==9 || boarddata[i+1][j] == NULL)
                        vertical = "B";
                    if (j == 0 || j==13 || boarddata[i][j-1] == NULL)
                        horizontal = "L";
                    else if (j == BOARD_SIZE_W - 1 || j==9 || boarddata[i][j+1] == NULL)
                        horizontal = "R";
//                    if (vertical != "N" || horizontal != "N")
                    background->setImage(50, 50, "border_" + vertical + horizontal + ".png");
                } else {
                    horizontal = "";
                    vertical = "";
                    if (boarddata[i - 1][j] < 0)
                        vertical += "T";
                    if (boarddata[i + 1][j] < 0)
                        vertical += "B";

                    if (boarddata[i][j - 1] < 0)
                        horizontal += "L";
                    if (boarddata[i][j + 1] < 0)
                        horizontal += "R";

                    background->setImage(50, 50, "wall_" + vertical + horizontal + ".png");
                }
            }
            else
                background = new Block(offsetX + 50 * j, offsetY + 50 * i);
            rooms[room(j, i)].push_back(background);
            scene()->addItem(background);
        }
    }
    file.close();
}

void Game::loadRoom(int room, int boarddata[BOARD_SIZE_H][BOARD_SIZE_W], int offsetX, int offsetY)
{
    QString temp;
    int tmp;
    int to = 0;
    GameObject *background;

    QFile file("Room" + QString::number(room) + ".txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:";
        qCritical() << file.errorString();
        return;
    }
    QTextStream stream(&file);

    for (int i = 0; i < BOARD_SIZE_H; i++)
    {
        for (int j = 0; j < BOARD_SIZE_W; j++)
        {
            stream >> temp;
            if (temp == "start")
            {
                boarddata[i][j] = 0;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;
                PXstart[room - 1] = offsetX + 50 * j;
                PYstart[room - 1] = offsetY + 50 * i;
            }
            else if (temp == "end")
            {
                boarddata[i][j] = 0;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;
                PXend[room - 1] = offsetX + 50 * j;
                PYend[room - 1] = offsetY + 50 * i;
            }
            else if (temp == "enemy1")
            {
                boarddata[i][j] = 0;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;
                Enemy *tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i);
                enemys[room - 1].push_back(tmp);
                tmp->setPtrs(&enemys[room - 1], enemys[room - 1].size() - 1);
                enemysPerRoom[room - 1]++;
            }
            else if (temp == "enemy2")
            {
                boarddata[i][j] = 0;
                //                 boarddata[2*i+1][2*j]=0;
                //                 boarddata[2*i][2*j+1]=0;
                //                 boarddata[2*i+1][2*j+1]=0;
                Enemy *tmp = new Enemy2(offsetX + 50 * j, offsetY + 50 * i);
                enemys[room - 1].push_back(tmp);
                tmp->setPtrs(&enemys[room - 1], enemys[room - 1].size() - 1);
                enemysPerRoom[room - 1]++;
            }
            else if (temp == "door1" || temp == "door2" || temp == "door3" || temp == "door4")
            {
                //                 boarddata[i][j]=-3;
                //                 boarddata[2*i+1][2*j]=-3;
                //                 boarddata[2*i][2*j+1]=-3;
                //                 boarddata[2*i+1][2*j+1]=-3;
                if (temp == "door1")
                    to = 0;
                else if (temp == "door2")
                    to = 1;
                else if (temp == "door3")
                    to = 2;
                else if (temp == "door4")
                    to = 3;
                boarddata[i][j] = -1 * (to + 3);
            }
            else
            {
                tmp = temp.toInt();
                boarddata[i][j] = tmp;
                //                 boarddata[2*i+1][2*j]=tmp;
                //                 boarddata[2*i][2*j+1]=tmp;
                //                 boarddata[2*i+1][2*j+1]=tmp;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE_H; i++)
    {
        for (int j = 0; j < BOARD_SIZE_W; j++)
        {

            if (boarddata[i][j] <= -3)
            {
                to = -1 * (boarddata[i][j]) - 3;
                if (room - 1 > to)
                    doors[room - 1][to] = new Door(offsetX + 50 * j, offsetY + 50 * i, room - 1, to); // opened
                else
                    doors[room - 1][to] = new Door(offsetX + 50 * j, offsetY + 50 * i, room - 1, to); // closed
                background = doors[room - 1][to];
                boarddata[i][j] = -3;
            }
            else if (boarddata[i][j] < 0)
            {
                background = new Wall(offsetX + 50 * j, offsetY + 50 * i, boarddata[i][j]);
                QString vertical = "N", horizontal = "N";
                if (i == 0 || i==13)
                    vertical = "T";
                else if (i == BOARD_SIZE_H - 1 || i==9)
                    vertical = "B";
                if (j == 0 || j==13)
                    horizontal = "L";
                else if (j == BOARD_SIZE_W - 1 || j==9)
                    horizontal = "R";

                if (vertical != "N" || horizontal != "N")
                    background->setImage(50, 50, "border_" + vertical + horizontal + ".png");
                else
                {
                    horizontal = "";
                    vertical = "";
                    if (boarddata[i - 1][j] < 0)
                        vertical += "T";
                    if (boarddata[i + 1][j] < 0)
                        vertical += "B";

                    if (boarddata[i][j - 1] < 0)
                        horizontal += "L";
                    if (boarddata[i][j + 1] < 0)
                        horizontal += "R";

                    background->setImage(50, 50, "wall_" + vertical + horizontal + ".png");
                }
            }
            else
                background = new Block(offsetX + 50 * j, offsetY + 50 * i);
            rooms[room - 1].push_back(background);
            scene()->addItem(background);
        }
    }
    file.close();
}

void Game::start()
{
    view->setSceneRect(viewOffset[0], viewOffset[1], 1300, 750);
//    view->setSceneRect(0, 0, 1300, 2100);
    resume();
}

void Game::run()
{
    if (!running)
        return;

    frame++;
    frame %= 1000;
    for (int _=0; _<ROOM_COUNT; _++)
    {
        for (int i = 0; i < rooms[_].size() && running; i++)
        {
            if (rooms[_][i] != NULL)
                rooms[_][i]->update(frame);
        }
        for (int i = 0; i < enemys[_].size() && running; i++)
        {
            if (enemys[_][i] != NULL)
                enemys[_][i]->update(frame);
        }
    }
    if (running)
        p->update(frame);
}

void Game::pauseMenu()
{
    pause();
    showPauseMenu(1350/2+viewOffset[0]-400/2, 750/2+viewOffset[1]-400/2);
}

void Game::pause()
{
    running = false;
    timer->stop();
}

void Game::resume()
{
    running = true;
    timer->start(33);
    p->setFocus();
}

void Game::musicOn()
{
    player->play();
}

void Game::musicOff()
{
    player->stop();
}

void Game::Win()
{
    if (!running)
        return;
    pause();
    musicOff();
    p->Hide();
    scene()->removeItem(p);

    status.setMsg(QString("You Win!"), 300 + 600 * currentRoom, 300);
    status.Show();
}

void Game::Lose()
{
    if (!running)
        return;
    pause();
    musicOff();
    p = NULL;
    for (int i = 0; i < enemys[currentRoom].size(); i++)
    {
        if (enemys[currentRoom][i] != NULL)
        {
            //            delete enemys[currentRoom][i];
            enemys[currentRoom][i]->ClearBullets(false);
            enemys[currentRoom][i]->Hide();
            scene()->removeItem(enemys[currentRoom][i]);
        }
    }

    status.setMsg(QString("Game Over!"), 300 + 600 * currentRoom, 300);
    status.Show();
}

void Game::switchRoom(int r)
{
    int fromRoom = r/10;
    int newRoom = r%10;

    if (currentRoom != newRoom)
        return;

    Door *doorptr = qgraphicsitem_cast<Door *>(doors[currentRoom][fromRoom]);
    if (!doorptr->open)
        return;
//    if (currentRoom < newRoom)
//    {
//        p->setPos(PXstart[newRoom], PYstart[newRoom]);
//    }
//    else if (currentRoom > newRoom)
//        p->setPos(PXend[newRoom], PYend[newRoom]);
    currentRoom = fromRoom;
    if (newRoom == 1 && fromRoom == 2)
    {
        view->setSceneRect(0, 600, 1300, 750);
        viewOffset[0] = 0;
        viewOffset[1] = 600;
        pauseButton.setPos(viewOffset[0]+25, viewOffset[1]+25);
    }
    else if (newRoom == 2 && fromRoom == 1)
    {
        view->setSceneRect(0, 0, 1300, 750);
        viewOffset[0] = 0;
        viewOffset[1] = 0;
        pauseButton.setPos(viewOffset[0]+25, viewOffset[1]+25);
    }
}

void Game::decrementEnemy()
{
    if (!running)
        return;
    enemysPerRoom[currentRoom]--;
    if (enemysPerRoom[currentRoom] <= 0)
    {
        if (currentRoom == 3)
            Win();
        else
        {
            doors[currentRoom][currentRoom+1]->unlock();
            doors[currentRoom+1][currentRoom]->unlock();
        }
    }
}

Game::~Game() {}
