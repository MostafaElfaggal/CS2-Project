#include <QVector>
#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QBrush>

#include <QFile>
#include <QTextStream>

#include "mainmenu.h"

#include "gameobject.h"
#include "game.h"

#include "grass.h"
#include "wall.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"
#include "Button.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QVector<GameObject *> objs;
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsView view;
    view.setFixedSize(610, 610);
    view.setWindowTitle("Game");
    view.setBackgroundBrush(QBrush(Qt::black));

    QFile file("Board.txt");
    if (! file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:";
        qCritical() << file.errorString();
        return 1;
    }
    QTextStream stream(&file);

    int boarddata[20][20];
    QString temp;
    int tmp;
    GameObject *background[10][10];
    int PX = 100, PY = 100;
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
                 objs.push_back(tmp);
             }else {
                 tmp = temp.toInt();
                 boarddata[2*i][2*j]=tmp;
                 boarddata[2*i+1][2*j]=tmp;
                 boarddata[2*i][2*j+1]=tmp;
                 boarddata[2*i+1][2*j+1]=tmp;
             }

             if(boarddata[2*i][2*j]<0)
                 background[i][j] = new Wall(50+50*j,50+50*i);
             else
                 background[i][j] = new Grass(50+50*j,50+50*i);
             objs.push_back(background[i][j]);
             scene.addItem(background[i][j]);
            }
    }
    file.close();

///////////////////////////////////////////////////////////////////////////////////////// Enemys
    for (int i=0; i<enemys.size(); i++) {
        scene.addItem(enemys[i]);
    }
/////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    Player p(PX, PY);
    objs.push_back(&p);
    scene.addItem(&p);

    p.setFlag(QGraphicsItem::ItemIsFocusable);
    p.setFocus();
/////////////////////////////////////////////////////////////////////////////////////////
    view.setScene(&scene);
    view.setSceneRect(0, 0, 600, 600);

    Game g(&objs);
//    MainMenu m;
//    scene.addItem(&m);
//    m.displaymenu();

    view.show();

    return a.exec();
}
