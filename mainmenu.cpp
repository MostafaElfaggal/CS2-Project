#include "mainmenu.h"

#include <QDebug>

#include <QApplication>

MainMenu::MainMenu() : QGraphicsRectItem(QRect(50,50,500,500))
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
    int bxPos = 300 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton -> setPos(bxPos,byPos);

    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));

    scene()->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos = 300 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton -> setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene()->addItem(quitButton);

    Button* musicButton = new Button(QString("Music"));
    int mxPos = 300 - musicButton->boundingRect().width()/2;
    int myPos = 425;
    musicButton -> setPos(mxPos,myPos);
    connect(musicButton,SIGNAL(clicked()),this,SLOT(music()));
    scene()->addItem(musicButton);
}

void MainMenu::start()
{
    qDebug() << "Starting";
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

