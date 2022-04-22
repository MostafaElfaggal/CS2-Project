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

    void music();
    void close();
    void start();
};

#endif // MAINMENU_H
