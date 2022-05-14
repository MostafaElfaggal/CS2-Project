#include "menu.h"

#include <QDebug>

#include <QApplication>

bool Menu::isMusicRunning = true;

Menu::Menu(Game* g, int size_w, int size_h) : QGraphicsPixmapItem(QPixmap("menu.png"))
{
    connect(this,SIGNAL(musicOn()),g,SLOT(musicOn()));
    connect(this,SIGNAL(musicOff()),g,SLOT(musicOff()));

    QPixmap p("menu.png");
    p = p.scaledToHeight(size_h);
    p = p.scaledToWidth(size_w);
    setPixmap(p);

//    setBrush(QBrush(Qt::blue));

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
    int tyPos = y()+h/50;
    titleText->setPos(txPos,tyPos);
    titleText->setZValue(11);

    int bxPos = x() + w/2 - playButton->boundingRect().width()/2;
    int byPos = y()+(h*1/5);
    playButton -> setLoc(bxPos,byPos);

    int mxPos = x() + w/2 - musicButton->boundingRect().width()/2;
    int myPos = y()+(h*2/5);
    musicButton -> setLoc(mxPos,myPos);

    int qxPos = x() + w/2 - quitButton->boundingRect().width()/2;
    int qyPos = y()+(h*3/5);
    quitButton -> setLoc(qxPos,qyPos);
}

void Menu::init(int x_pos, int y_pos, QString btn1_msg)
{
    titleText = new QGraphicsTextItem(QString("Game Name"));
    QFont titleFont("Times New Roman",25);
    titleText->setFont(titleFont);
    scene()->addItem(titleText);

    playButton = new ClickableImage(200, 50, "Play Button Normal.png", "Play Button Hover.png", "Play Button Clicked.png", 250, 100);
    connect(playButton,SIGNAL(press()),this,SLOT(btn1()));
    scene()->addItem(playButton);

//    musicButton = new Button(QString("Music: ON"), 200, 50);
    musicButton = new ClickableImage(200, 50, "Music On Button Normal.png", "Music On Button Hover.png", "Music On Button Clicked.png", 250, 100);
    connect(musicButton,SIGNAL(press()),this,SLOT(music()));
    scene()->addItem(musicButton);

//    quitButton= new Button(QString("Quit"), 200, 50);
    quitButton = new ClickableImage(200, 50, "Exit Button Normal.png", "Exit Button Hover.png", "Exit Button Clicked.png", 250, 100);
    connect(quitButton,SIGNAL(press()),this,SLOT(close()));
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
     musicButton->setImage("Music Off Button Normal.png", "Music Off Button Hover.png", "Music Off Button Clicked.png", 250, 100);
     isMusicRunning = false;
     musicOff();
 } else {
     musicButton->setImage("Music On Button Normal.png", "Music On Button Hover.png", "Music On Button Clicked.png", 250, 100);
     isMusicRunning = true;
     musicOn();
 }
}

