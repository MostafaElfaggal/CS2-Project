#include "game.h"

#include <QDebug>
#include <QTimer>

#include <QFile>
#include <QTextStream>

#include "mainmenu.h"

#include "gameobject.h"

#include "grass.h"
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
    int boarddata[3][20][20];

    loadRoom(1, boarddata[0], 50, 50);
    loadRoom(2, boarddata[0], 650, 50);
    loadRoom(3, boarddata[0], 1250, 50);

///////////////////////////////////////////////////////////////////////////////////////// Enemys
    for (int i=0; i<enemys.size(); i++) {
        scene()->addItem(enemys[i]);
    }
/////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    p.setPos(PXstart[0], PYstart[0]);
//    rooms[0].push_back(&p);
    scene()->addItem(&p);

    p.setFocus();
/////////////////////////////////////////////////////////////////////////////////////////

    currentRoom = 0;

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
                 GameObject* tmp = new Enemy1(offsetX+50*j, offsetY+50*i);
                 enemys.push_back(tmp);
                 rooms[room-1].push_back(tmp);
             } else if (temp == "enemy2") {
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 GameObject* tmp = new Enemy2(offsetX+50*j, offsetY+50*i);
                 enemys.push_back(tmp);
                 rooms[room-1].push_back(tmp);
             } else if(temp == "door1" || temp == "door2" || temp == "door3") {
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
             } else {
                 tmp = temp.toInt();
                 boarddata[2*i][2*j]=tmp;
                 boarddata[2*i+1][2*j]=tmp;
                 boarddata[2*i][2*j+1]=tmp;
                 boarddata[2*i+1][2*j+1]=tmp;
             }

             if (boarddata[2*i][2*j] == -3)
             {
                 background = new Door(offsetX+50*j,offsetY+50*i, room-1, to);
                 doors[room-1] = background;
             }
             else if(boarddata[2*i][2*j]<0)
                 background = new Wall(offsetX+50*j,offsetY+50*i, boarddata[2*i][2*j]);
             else
                 background = new Grass(offsetX+50*j,offsetY+50*i);
             rooms[room-1].push_back(background);
             scene()->addItem(background);
            }
    }
    file.close();
}

void Game::run() {
    frame++;
    frame %= 1000;
    for (int i=0; i<rooms[currentRoom].size(); i++) {
        if (rooms[currentRoom][i] != NULL)
            rooms[currentRoom][i]->update(frame);
    }
    p.update(frame);
}

void Game::switchRoom(int newRoom)
{
    if (currentRoom < newRoom)
        p.setPos(PXstart[newRoom], PYstart[newRoom]);
    else
        p.setPos(PXend[newRoom], PYend[newRoom]);
    currentRoom = newRoom;
    view->setSceneRect(600*currentRoom, 0, 600, 600);
}

Game::~Game() {}
