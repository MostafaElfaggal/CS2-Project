#include "pausemenu.h"

PauseMenu::PauseMenu(Game* g) : Menu(g, 400, 540)
{
    connect(g,SIGNAL(showPauseMenu(float, float)),this,SLOT(Show(float, float)));
    connect(g,SIGNAL(hidePauseMenu()),this,SLOT(Hide()));
    connect(this,SIGNAL(resumeGame()),g,SLOT(resume()));
}

void PauseMenu::btn1()
{
    Hide();
    resumeGame();
}

void PauseMenu::Show(float x_pos, float y_pos)
{
    playButton->setImage("Resume Button Normal.png", "Resume Button Hover.png", "Resume Button Clicked.png", 250, 100);
    if (isMusicRunning)
        musicButton->setImage("Music On Button Normal.png", "Music On Button Hover.png", "Music On Button Clicked.png", 250, 100);
    else
        musicButton->setImage("Music Off Button Normal.png", "Music Off Button Hover.png", "Music Off Button Clicked.png", 250, 100);

    displaymenu(x_pos, y_pos);

    titleText->setZValue(100);
    playButton->setZValue(100);
    quitButton->setZValue(100);
    musicButton->setZValue(100);
    setZValue(99);

    titleText->show();
    playButton->show();
    quitButton->show();
    musicButton->show();
    show();
}

void PauseMenu::Hide()
{
    titleText->hide();
    playButton->hide();
    quitButton->hide();
    musicButton->hide();
    hide();
}
