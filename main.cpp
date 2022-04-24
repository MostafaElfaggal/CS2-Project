#include <QVector>
#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "mainwindow.h"

#include "mainmenu.h"

#include "game.h"

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
    view.setSceneRect(0, 600, 600, 600);

    MainWindow w(&view);
    w.show();

    Game g(&view);
    scene.addItem(&g);
    g.init();

    MainMenu m(&g);
    scene.addItem(&m);
    m.displaymenu();

//    view.show();

    return a.exec();
}
