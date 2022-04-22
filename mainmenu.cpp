#include "mainmenu.h"

MainMenu::MainMenu() : QGraphicsRectItem(QRect(200,0,200,600))
{
    setBrush(QBrush(Qt::blue));

}

void MainMenu::displaymenu()
{
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Game Name"));
    QFont titleFont("Comic Sans",50);
    titleText->setFont(titleFont);
    int txPos = 300 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);

    scene()->addItem(titleText);

    Button* playButton = new Button(QString("Start Game"));
    int bxPos=300 - titleText->boundingRect().width()/2;
    int byPos = 275;
    playButton -> setPos(bxPos,byPos);

    connect(playButton,SIGNAL(Clicked()),this,SLOT(start()));

    scene()->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos=300 - titleText->boundingRect().width()/2;
    int qyPos=350;
    quitButton -> setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(Clicked()),this,SLOT(close()));
    scene()->addItem(quitButton);

    Button* musicButton = new Button(QString("Music"));
    int mxPos=300 - titleText->boundingRect().width()/2;
    int myPos=425;
    musicButton -> setPos(mxPos,myPos);
    connect(musicButton,SIGNAL(Clicked()),this,SLOT(music()));
    scene()->addItem(musicButton);
}
