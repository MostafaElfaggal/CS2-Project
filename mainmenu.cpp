#include "mainmenu.h"

#include <QDebug>

#include <QApplication>

MainMenu::MainMenu() : QGraphicsRectItem(QRect(50,50,500,500))
{
    setBrush(QBrush(Qt::blue));
}

void MainMenu::displaymenu()
{
    float w=boundingRect().width(), h=boundingRect().height();

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Game Name"));
    QFont titleFont("Comic Sans",50);
    titleText->setFont(titleFont);
    int txPos = ((x()+w)/2) - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);

    scene()->addItem(titleText);

    Button* playButton = new Button(QString("Start Game"));
    int bxPos = ((x()+w)/2) - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton -> setPos(bxPos,byPos);

    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));

    scene()->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos = ((x()+w)/2) - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton -> setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene()->addItem(quitButton);

    Button* musicButton = new Button(QString("Music"));
    int mxPos = ((x()+w)/2) - musicButton->boundingRect().width()/2;
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

