#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "Button.h"
#include <QObject>


class MainMenu : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
public:

    MainMenu();
    void displaymenu();

    public slots:

    void start();
    void close();
    void music();
};

#endif // MAINMENU_H
