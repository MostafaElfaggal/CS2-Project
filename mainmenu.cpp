#include "mainmenu.h"

MainMenu::MainMenu(Game* g) : Menu(g, 551, 744)
{
    connect(this,SIGNAL(startGame()),g,SLOT(start()));
}

void MainMenu::background()
{
    QPixmap bgimg("Menu_background.png");
    bg.setPixmap(bgimg);
    bg.setZValue(1);
    bg.setPos(0, 1350);
    scene()->addItem(&bg);
}

void MainMenu::btn1()
{
    startGame();
}
