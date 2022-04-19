#include <QApplication>

#include <QDir>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QBrush>

#include <QFile>
#include <QTextStream>

#include "gameobject.h"
#include "game.h"

#include "grass.h"
#include "wall.h"
#include "player.h"
#include "enemy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent("D:/Projects/C++ Qt/CS2_Project");

    QGraphicsScene scene;

    QGraphicsView view;
    view.setFixedSize(610, 610);
    view.setWindowTitle("Game");
    view.setBackgroundBrush(QBrush(Qt::black));

    QFile file("Board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    int boarddata[10][10];
    QString temp;
    GameObject *background[10][10];
    for (int i=0;i<10;i++)
            for (int j=0;j<10;j++)
            {
             stream>>temp;
             boarddata[i][j]=temp.toInt();

             if(boarddata[i][j]<0)
                 background[i][j] = new Wall(50+50*j,50+50*i);
             else
                 background[i][j] = new Grass(50+50*j,50+50*i);
             scene.addItem(background[i][j]);
            }
    Player p(100, 100);
    scene.addItem(&p);

    view.setScene(&scene);
    view.setSceneRect(0, 0, 600, 600);
    view.show();



    return a.exec();
}
