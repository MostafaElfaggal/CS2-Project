#include "mainmenu.h"

MainMenu::MainMenu(Game* g) : Menu(g, 500, 500)
{
    connect(this,SIGNAL(startGame()),g,SLOT(start()));
}

void MainMenu::btn1()
{
    startGame();
}
