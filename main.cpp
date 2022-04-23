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
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsView view;
    view.setFixedSize(610, 610);
    view.setWindowTitle("Game");
    view.setBackgroundBrush(QBrush(Qt::black));

    view.setScene(&scene);
    view.setSceneRect(0, 0, 600, 600);

    Game g;
    scene.addItem(&g);
    g.init();


//    MainMenu m;
//    scene.addItem(&m);
//    m.displaymenu();

    view.show();

    return a.exec();
}
