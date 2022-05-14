#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"

class MainMenu : public Menu
{
    Q_OBJECT
private:
    QGraphicsPixmapItem bg;

public:
    MainMenu(Game* g);
    void background();

public slots:
    void btn1();
};

#endif // MAINMENU_H
