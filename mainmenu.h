#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>

#include "game.h"
#include "Button.h"


class MainMenu : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
private:
    QGraphicsView* view;
public:

    MainMenu(Game* g);
    void displaymenu();

public slots:
    void start();
    void close();
    void music();
signals:
    void startGame();
};

#endif // MAINMENU_H
