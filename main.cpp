#include <QVector>
#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "mainwindow.h"

#include "mainmenu.h"
#include "pausemenu.h"

#include "game.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsView view;
    view.setFixedSize(1310, 760);
    view.setWindowTitle("Game");
    view.setBackgroundBrush(QBrush(Qt::black));

    view.setScene(&scene);
    view.setSceneRect(0, 1350, 1300, 750);

//    MainWindow w(&view);
//    w.show();

    Game g(&view);
    scene.addItem(&g);
    g.init();

    MainMenu m(&g);
    scene.addItem(&m);
    m.background();
    m.init(1300/2-551/2, (1350+750/2)-744/2, "Start Game");

    PauseMenu m2(&g);
    scene.addItem(&m2);
    m2.init(0, 0, "Resume Game");
    m2.Hide();

    view.show();

    return a.exec();
}
