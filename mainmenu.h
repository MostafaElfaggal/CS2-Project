#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMediaPlayer>
#include <QAudioOutput>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>

#include "game.h"
#include "Button.h"


class MainMenu : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
private:
    QGraphicsView* view;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

    bool isMusicRunning;

    QGraphicsTextItem* titleText;
    Button* playButton;
    Button* quitButton;
    Button* musicButton;

public:

    MainMenu(Game* g);
    void displaymenu();

public slots:
    void start();
    void close();
    void music();

    void musicOn();
    void musicOff();

signals:
    void startGame();
};

#endif // MAINMENU_H
