#include "mainmenu.h"

#include <QDebug>

#include <QApplication>

MainMenu::MainMenu(Game* g) : QGraphicsRectItem(QRect(0,0,500,500))
{
    connect(this,SIGNAL(startGame()),g,SLOT(start()));

    setBrush(QBrush(Qt::blue));
    setPos(50, 650);
}

void MainMenu::displaymenu()
{
    float w=boundingRect().width();
//    float h=boundingRect().height();

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Game Name"));
    QFont titleFont("Comic Sans",50);
    titleText->setFont(titleFont);
    int txPos = x() + w/2 - titleText->boundingRect().width()/2;
    int tyPos = y()+100;
    titleText->setPos(txPos,tyPos);

    scene()->addItem(titleText);

    Button* playButton = new Button(QString("Start Game"));
    int bxPos = x() + w/2 - playButton->boundingRect().width()/2;
    int byPos = y()+225;
    playButton -> setPos(bxPos,byPos);

    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));

    scene()->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos = x() + w/2 - quitButton->boundingRect().width()/2;
    int qyPos = y()+300;
    quitButton -> setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene()->addItem(quitButton);

    Button* musicButton = new Button(QString("Music"));
    int mxPos = x() + w/2 - musicButton->boundingRect().width()/2;
    int myPos = y()+375;
    musicButton -> setPos(mxPos,myPos);
    connect(musicButton,SIGNAL(clicked()),this,SLOT(music()));
    scene()->addItem(musicButton);
}

void MainMenu::start()
{
    qDebug() << "Starting";
    startGame();
}

void MainMenu::close()
{
    QApplication::quit();
    qDebug() << "closing";
}

void MainMenu::music()
{
 qDebug() << "Music";
}

