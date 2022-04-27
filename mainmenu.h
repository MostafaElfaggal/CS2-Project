#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"

class MainMenu : public Menu
{
    Q_OBJECT
public:
    MainMenu(Game* g);

public slots:
    void btn1();
};

#endif // MAINMENU_H
