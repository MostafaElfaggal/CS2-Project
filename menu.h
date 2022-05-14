#ifndef MENU_H
#define MENU_H

#include <QMediaPlayer>
#include <QAudioOutput>

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>

#include "game.h"
#include "Button.h"
#include "clickableimage.h"


class Menu : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QGraphicsView* view;


protected:
    QGraphicsTextItem* titleText;
    ClickableImage* playButton;
    ClickableImage* quitButton;
    ClickableImage* musicButton;

public:
    static bool isMusicRunning;

    Menu(Game* g, int size_w, int size_h);
    void displaymenu(int x_pos, int y_pos);
    void init(int x_pos, int y_pos, QString btn1_msg);

public slots:
    virtual void btn1()=0;
    void close();
    void music();

signals:
    void musicOn();
    void musicOff();

    void startGame();
    void resumeGame();
};

#endif // MENU_H
