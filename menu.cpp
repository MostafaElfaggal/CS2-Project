#include "menu.h"

#include <QDebug>

#include <QApplication>

bool Menu::isMusicRunning = true;

Menu::Menu(Game* g, int size_w, int size_h) : QGraphicsRectItem(QRect(0,0,size_w,size_h))
{
    connect(this,SIGNAL(musicOn()),g,SLOT(musicOn()));
    connect(this,SIGNAL(musicOff()),g,SLOT(musicOff()));

    setBrush(QBrush(Qt::blue));

    setZValue(10);

    musicOn();
}

void Menu::displaymenu(int x_pos, int y_pos)
{
    prepareGeometryChange();
    setPos(x_pos, y_pos);
    float w=boundingRect().width();
    float h=boundingRect().height();

    int txPos = x() + w/2 - titleText->boundingRect().width()/2;
    int tyPos = y()+h/5;
    titleText->setPos(txPos,tyPos);
    titleText->setZValue(11);

    int bxPos = x() + w/2 - playButton->boundingRect().width()/2;
    int byPos = y()+h/2;
    playButton -> setLoc(bxPos,byPos);

    int mxPos = x() + w/2 - musicButton->boundingRect().width()/2;
    int myPos = y()+(h/2)+h*3/20;
    musicButton -> setLoc(mxPos,myPos);

    int qxPos = x() + w/2 - quitButton->boundingRect().width()/2;
    int qyPos = y()+(h/2)+h*6/20;
    quitButton -> setLoc(qxPos,qyPos);
}

void Menu::init(int x_pos, int y_pos, QString btn1_msg)
{
    titleText = new QGraphicsTextItem(QString("Game Name"));
    QFont titleFont("Comic Sans",40);
    titleText->setFont(titleFont);
    scene()->addItem(titleText);

    playButton = new Button(QString(btn1_msg), 200, 50);
    connect(playButton,SIGNAL(clicked()),this,SLOT(btn1()));
    scene()->addItem(playButton);

    musicButton = new Button(QString("Music: ON"), 200, 50);
    connect(musicButton,SIGNAL(clicked()),this,SLOT(music()));
    scene()->addItem(musicButton);

    quitButton= new Button(QString("Quit"), 200, 50);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene()->addItem(quitButton);

    displaymenu(x_pos, y_pos);
}

void Menu::close()
{
    QApplication::quit();
}

void Menu::music()
{
 if (isMusicRunning)
 {
     musicButton->setText(QString("Music: OFF"));
     isMusicRunning = false;
     musicOff();
 } else {
     musicButton->setText(QString("Music: ON"));
     isMusicRunning = true;
     musicOn();
 }
}

