#include "game.h"

#include <QDebug>
#include <QTimer>

#include <QFile>
#include <QTextStream>

#include "mainmenu.h"

#include "gameobject.h"

#include "grass.h"
#include "wall.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"
#include "Button.h"

Game::Game() : QGraphicsRectItem(QRect(0,0,1,1)), p(0, 0)
{
    frame = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
}

void Game::init()
{
    QFile file("Board.txt");
    if (! file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:";
        qCritical() << file.errorString();
        return;
    }
    QTextStream stream(&file);

    int boarddata[20][20];
    QString temp;
    int tmp;
    GameObject *background;
    int PX = 0, PY = 0;
    QVector<GameObject*> enemys;

    for (int i=0;i<10;i++)
    {
            for (int j=0;j<10;j++)
            {
             stream>>temp;
             if (temp == "*"){
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 PX = 50+50*j;
                 PY = 50+50*i;
             } else if (temp == "enemy") {
                 boarddata[2*i][2*j]=0;
                 boarddata[2*i+1][2*j]=0;
                 boarddata[2*i][2*j+1]=0;
                 boarddata[2*i+1][2*j+1]=0;
                 GameObject* tmp = new Enemy1(50+50*j, 50+50*i);
                 enemys.push_back(tmp);
                 rooms[0].push_back(tmp);
             }else {
                 tmp = temp.toInt();
                 boarddata[2*i][2*j]=tmp;
                 boarddata[2*i+1][2*j]=tmp;
                 boarddata[2*i][2*j+1]=tmp;
                 boarddata[2*i+1][2*j+1]=tmp;
             }

             if(boarddata[2*i][2*j]<0)
                 background = new Wall(50+50*j,50+50*i);
             else
                 background = new Grass(50+50*j,50+50*i);
             rooms[0].push_back(background);
             scene()->addItem(background);
            }
    }
    file.close();

///////////////////////////////////////////////////////////////////////////////////////// Enemys
    for (int i=0; i<enemys.size(); i++) {
        scene()->addItem(enemys[i]);
    }
/////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    p.setPos(PX, PY);
//    rooms[0].push_back(&p);
    scene()->addItem(&p);

    p.setFocus();
/////////////////////////////////////////////////////////////////////////////////////////

    currentRoom = 0;

    timer->start(33);
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

Game::~Game() {}
