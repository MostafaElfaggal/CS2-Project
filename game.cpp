#include "game.h"

#include <QDebug>
#include <QTimer>

#include <QFile>
#include <QTextStream>

#include "mainmenu.h"

#include "block.h"
#include "wall.h"
#include "door.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"
#include "Button.h"

Game::Game(QGraphicsView* v) : QGraphicsRectItem(QRect(0,0,1,1)), p(0, 0)
{
    view = v;

    frame = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    connect(&p,SIGNAL(callSwitchView(int)),this,SLOT(switchRoom(int)));
}

void Game::init()
{
    int boarddata[ROOM_COUNT][20][20];

    enemysPerRoom[0] = 0;
    enemysPerRoom[1] = 0;
    enemysPerRoom[2] = 0;
    enemysPerRoom[3] = 0;

    for (int i=1; i<=ROOM_COUNT; i++)
        loadRoom(i, boarddata[i-1], 50+600*(i-1), 50);

///////////////////////////////////////////////////////////////////////////////////////// Enemys
    for (int _=0; _<ROOM_COUNT; _++)
        for (int i=0; i<enemys[_].size(); i++) {
            scene()->addItem(enemys[_][i]);
            enemys[_][i]->init();
            connect(enemys[_][i],SIGNAL(die()),this,SLOT(decrementEnemy()));
        }
/////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    p.setPos(PXstart[0], PYstart[0]);
    scene()->addItem(&p);
    p.init();

    p.setFocus();
/////////////////////////////////////////////////////////////////////////////////////////

    currentRoom = 0;
    running = false;

    timer->start(33);
}

void Game::loadRoom(int room, int boarddata[20][20], int offsetX, int offsetY)
{
    QString temp;
    int tmp;
    int to = 0;
    GameObject *background;

    QFile file("Room" + QString::number(room) + ".txt");
    if (! file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:";
        qCritical() << file.errorString();
        return;
    }
    QTextStream stream(&file);


    for (int i=0;i<10;i++)
    {
            for (int j=0;j<10;j++)
            {
             stream>>temp;
             if (temp == "start"){
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 PXstart[room-1] = offsetX+50*j;
                 PYstart[room-1] = offsetY+50*i;
             } else if (temp == "end") {
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 PXend[room-1] = offsetX+50*j;
                 PYend[room-1] = offsetY+50*i;
             } else if (temp == "enemy1") {
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 Enemy* tmp = new Enemy1(offsetX+50*j, offsetY+50*i);
                 enemys[room-1].push_back(tmp);
                 tmp->setPtrs(&enemys[room-1].last());
                 enemysPerRoom[room-1]++;
             } else if (temp == "enemy2") {
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 Enemy* tmp = new Enemy2(offsetX+50*j, offsetY+50*i);
                 enemys[room-1].push_back(tmp);
                 tmp->setPtrs(&enemys[room-1].last());
                 enemysPerRoom[room-1]++;
             } else if(temp == "door1" || temp == "door2" || temp == "door3" || temp == "door4") {
                 boarddata[2*i][2*j]=-3;
                 boarddata[2*i+1][2*j]=-3;
                 boarddata[2*i][2*j+1]=-3;
                 boarddata[2*i+1][2*j+1]=-3;
                 if (temp == "door1")
                     to = 0;
                 else if (temp == "door2")
                     to = 1;
                 else if (temp == "door3")
                     to = 2;
                 else if (temp == "door4")
                     to = 3;
             } else {
                 tmp = temp.toInt();
                 boarddata[2*i][2*j]=tmp;
                 boarddata[2*i+1][2*j]=tmp;
                 boarddata[2*i][2*j+1]=tmp;
                 boarddata[2*i+1][2*j+1]=tmp;
             }

             if (boarddata[2*i][2*j] == -3)
             {
                 if (room-1 > to)
                     doors[room-1][to] = new Door(offsetX+50*j,offsetY+50*i, room-1, to, true); // opened
                 else
                     doors[room-1][to] = new Door(offsetX+50*j,offsetY+50*i, room-1, to); // closed
                 background = doors[room-1][to];
             }
             else if(boarddata[2*i][2*j]<0)
                 background = new Wall(offsetX+50*j,offsetY+50*i, boarddata[2*i][2*j]);
             else
                 background = new Block(offsetX+50*j,offsetY+50*i);
             rooms[room-1].push_back(background);
             scene()->addItem(background);
            }
    }
    file.close();
}

void Game::run() {
    if (!running)
        return;

    frame++;
    frame %= 1000;
    for (int i=0; i<rooms[currentRoom].size(); i++) {
        if (rooms[currentRoom][i] != NULL)
            rooms[currentRoom][i]->update(frame);
    }
    for (int i=0; i<enemys[currentRoom].size(); i++) {
        if (enemys[currentRoom][i] != NULL)
            enemys[currentRoom][i]->update(frame);
    }
    p.update(frame);
}

void Game::switchRoom(int newRoom)
{
    Door* doorptr = qgraphicsitem_cast<Door*>(doors[currentRoom][newRoom]);
    if (!doorptr->open)
        return;
    if (currentRoom < newRoom)
    {
        p.setPos(PXstart[newRoom], PYstart[newRoom]);
    }
    else
        p.setPos(PXend[newRoom], PYend[newRoom]);
    currentRoom = newRoom;
    view->setSceneRect(600*currentRoom, 0, 600, 600);
}

void Game::decrementEnemy()
{
    enemysPerRoom[currentRoom]--;
    if (enemysPerRoom[currentRoom] <= 0)
        doors[currentRoom][currentRoom+1]->unlock();
}

Game::~Game() {}

void Game::start()
{
    qDebug() << "here";
    view->setSceneRect(0, 0, 600, 600);
    running = true;
}
