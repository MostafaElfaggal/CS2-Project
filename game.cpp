#include "game.h"

#include <QDebug>
#include <QTimer>

#include <QFile>
#include <QTextStream>

#include "menu.h"

#include "block.h"
#include "wall.h"
#include "door.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"
#include "boss.h"
#include "Button.h"

int Game::room(int x_pos, int y_pos)
{
    // 0 1
    // 3 2
    int res = 0;
    if (y_pos < 10)
    {
        if (x_pos < 10)
            res = 0;
        else
            res = 1;
    }
    else
    {
        if (x_pos < 10)
            res = 3;
        else
            res = 2;
    }

    return res;
}

Game::Game(QGraphicsView *v) : QGraphicsRectItem(QRect(0, 0, 1, 1)), pauseButton(25, 25, "pauseBtn.png", "pauseBtn-hover", "pauseBtn-pressed.png", 50, 50), HealthBar("health_bar", 50, 635)
{
    p = new Player(0, 0);

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("song.mp3"));
    audioOutput->setVolume(50);

    view = v;
    viewOffset[0] = 0;
    viewOffset[1] = 0;

    frame = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    connect(p, SIGNAL(callSwitchView(int)), this, SLOT(switchRoom(int)));
}

void Game::init()
{
    enemysPerRoom[0] = 0;
    enemysPerRoom[1] = 0;
    enemysPerRoom[2] = 0;
    enemysPerRoom[3] = 0;

    loadWorld(); // enemies/blocks/walls/doors

    ///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    p->setPos(Pstart[0], Pstart[1]);
    scene()->addItem(p);
    p->init();
    connect(p, SIGNAL(die(int)), this, SLOT(Lose()));
//    connect(p, SIGNAL(changeHealth(float)), this, SLOT(playerHealthChanged(float)));
    /////////////////////////////////////////////////////////////////////////////////////////

    scene()->addItem(&status);
    status.init();

    scene()->addItem(&HealthBar);
    HealthBar.init();
    HealthBar.setZValue(8);
    connect(p, SIGNAL(changeHealth(float)), &HealthBar, SLOT(updateValue(float)));

    scene()->addItem(&pauseButton);
    connect(&pauseButton, SIGNAL(press()), this, SLOT(pauseMenu()));
    //    connect(&pauseButton,SIGNAL(resume()),this,SLOT(resume()));

    currentRoom = 0;
    running = false;
}

void Game::loadWorld()
{
    QString temp;
    int tmp;
    int to = 0;
    GameObject *background;

    QFile file("World.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Could not open file:";
        qCritical() << file.errorString();
        return;
    }
    QTextStream stream(&file);

    for (int i = 0; i < BOARD_SIZE_H; i++)
    {

        for (int j = 0; j < BOARD_SIZE_W; j++)
        {
            stream >> temp;
            if (temp == "//") // blank spot
                boarddata[i][j] = NULL;
            else if (temp == "st")
            { // starting point of the world
                boarddata[i][j] = 1;

                Pstart[0] = offsetX + 50 * j;
                Pstart[1] = offsetY + 50 * i;
            }
            else if (temp == "e1")
            { // enemy1
                boarddata[i][j] = 1;

                Enemy *tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i, room(j,i));
                enemysPerRoom[room(j, i)]++;

                scene()->addItem(tmp);
                tmp->init();
                connect(tmp, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
            }
            else if (temp == "e2")
            { // enemy2
                boarddata[i][j] = 1;
                Enemy *tmp = new Enemy2(offsetX + 50 * j, offsetY + 50 * i, room(j,i));
                enemysPerRoom[room(j, i)]++;

                scene()->addItem(tmp);
                tmp->init();
                connect(tmp, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
            } else if (temp == "bs")
            {
                boarddata[i][j] = 1;
                Enemy *tmp = new Boss(offsetX + 50 * j, offsetY + 50 * i, room(j,i));
                enemysPerRoom[room(j, i)]++;

                scene()->addItem(tmp);
                tmp->init();
                connect(tmp, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
            } else if (temp == "d1" || temp == "d2" || temp == "d3" || temp == "d4")
            { // doors
                if (temp == "d1")
                    to = 0;
                else if (temp == "d2")
                    to = 1;
                else if (temp == "d3")
                    to = 2;
                else if (temp == "d4")
                    to = 3;
                boarddata[i][j] = -1 * (to + 3);
            }
            else
            {
                tmp = temp.toInt();
                boarddata[i][j] = tmp;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE_H; i++)
    {
        for (int j = 0; j < BOARD_SIZE_W; j++)
        {
            if (boarddata[i][j] == NULL)
                continue;
            else if (boarddata[i][j] <= -3)
            {

                to = -1 * (boarddata[i][j]) - 3;
                doors[room(j, i)][to] = new Door(offsetX + 50 * j, offsetY + 50 * i, room(j, i), to);
                background = doors[room(j, i)][to];
                boarddata[i][j] = -3;
            }
            else if (boarddata[i][j] < 0)
            {
                background = new Wall(offsetX + 50 * j, offsetY + 50 * i, boarddata[i][j]);
                QString vertical = "N", horizontal = "N";
                if (boarddata[i][j] == -2)
                {
                    if (i == 0 || i==13 || boarddata[i-1][j] == NULL)
                        vertical = "T";
                    else if (i == BOARD_SIZE_H - 1 || i==9 || boarddata[i+1][j] == NULL)
                        vertical = "B";
                    if (j == 0 || j==13 || boarddata[i][j-1] == NULL)
                        horizontal = "L";
                    else if (j == BOARD_SIZE_W - 1 || j==9 || boarddata[i][j+1] == NULL)
                        horizontal = "R";
                    background->setImage(50, 50, "border_" + vertical + horizontal + ".png");
                } else {
                    horizontal = "";
                    vertical = "";
                    if (boarddata[i - 1][j] < 0)
                        vertical += "T";
                    if (boarddata[i + 1][j] < 0)
                        vertical += "B";

                    if (boarddata[i][j - 1] < 0)
                        horizontal += "L";
                    if (boarddata[i][j + 1] < 0)
                        horizontal += "R";

                    background->setImage(50, 50, "wall_" + vertical + horizontal + ".png");
                }
            }
            else
                background = new Block(offsetX + 50 * j, offsetY + 50 * i);
            rooms[room(j, i)].push_back(background);
            scene()->addItem(background);
            background->init();
        }
    }
    file.close();
}

void Game::start()
{
    view->setSceneRect(viewOffset[0], viewOffset[1], 1300, 750);
//    view->setSceneRect(0, 0, 1300, 2100);
    resume();
}

void Game::run()
{
    if (!running)
        return;

    frame++;
    frame %= 1000;

    QList<QGraphicsItem*> items = scene()->items();

    QList<QGraphicsItem*>::iterator i;
    for (i = items.begin(); i != items.end() && running; ++i)
    {

        GameObject* itemptr = dynamic_cast<GameObject*>(*i);
        if (itemptr)
            itemptr->update(frame);
    }
}

void Game::pauseMenu()
{
    if (!running)
        return;

    pause();
    showPauseMenu(1350/2+viewOffset[0]-400/2, 750/2+viewOffset[1]-400/2);
}

void Game::pause()
{
    running = false;
    timer->stop();
}

void Game::resume()
{
    running = true;
    timer->start(33);
    p->setFocus();
}

void Game::musicOn()
{
    player->play();
}

void Game::musicOff()
{
    player->stop();
}

void Game::Win()
{
    if (!running)
        return;
    pause();
    musicOff();
    p->blockBullets();
    p->ClearBullets();
    p->Hide();
    scene()->removeItem(p);

    // clearing enemy bullets
    QVector<Enemy*> es;
    QVector<QGraphicsItem*> eps;
    QList<QGraphicsItem*> items = scene()->items();
    QList<QGraphicsItem*>::iterator i;
    for (i=items.begin(); i!=items.end(); i++)
    {
        Enemy* eptr = dynamic_cast<Enemy*>(*i);
        if (eptr)
            es.push_back(eptr);
    }

    for (auto i=es.begin(); i!=es.end(); ++i)
        (*i)->ClearBullets();

    // explosions
    items = scene()->items();
    for (i=items.begin(); i!=items.end(); i++)
    {
        if (typeid(*i) == typeid(Explosion))
            eps.push_back(*i);
    }
    for (auto i=eps.begin(); i!=eps.end(); ++i)
        delete (*i);

    status.setMsg(QString("You Win!"), 1350/2+viewOffset[0], 750/2+viewOffset[1]);
    status.Show();
}

void Game::Lose()
{
    if (!running)
        return;
    pause();
    musicOff();
    p->blockBullets();
    p->ClearBullets();
    p = NULL;

    // clearing enemy bullets and deleting enemies
    QVector<Enemy*> es;
    QVector<QGraphicsItem*> eps;
    QList<QGraphicsItem*> items = scene()->items();
    QList<QGraphicsItem*>::iterator i;
    for (i=items.begin(); i!=items.end(); i++)
    {
        Enemy* eptr = dynamic_cast<Enemy*>(*i);
        if (eptr)
            es.push_back(eptr);
    }

    for (auto i=es.begin(); i!=es.end(); ++i)
    {
        (*i)->isExplode = false;
        (*i)->ClearBullets();
        delete (*i);
    }

    // explosions
    items = scene()->items();
    for (i=items.begin(); i!=items.end(); i++)
    {
        if (typeid(*i) == typeid(Explosion))
            eps.push_back(*i);
    }
    for (auto i=eps.begin(); i!=eps.end(); ++i)
        delete (*i);

    status.setMsg(QString("Game Over!"), 1350/2+viewOffset[0], 750/2+viewOffset[1]);
    status.Show();
}

void Game::switchRoom(int r)
{
    int fromRoom = r/10;
    int newRoom = r%10;

    if (currentRoom != newRoom)
        return;

    Door *doorptr = qgraphicsitem_cast<Door *>(doors[currentRoom][fromRoom]);
    if (!doorptr->open)
        return;

    currentRoom = fromRoom;
    if (newRoom == 1 && fromRoom == 2)
    {
        view->setSceneRect(0, 600, 1300, 750);
        viewOffset[0] = 0;
        viewOffset[1] = 600;
        pauseButton.setPos(viewOffset[0]+25, viewOffset[1]+25);
        HealthBar.setLoc(50, viewOffset[1]+662.5);
    }
    else if (newRoom == 2 && fromRoom == 1)
    {
        view->setSceneRect(0, 0, 1300, 750);
        viewOffset[0] = 0;
        viewOffset[1] = 0;
        pauseButton.setPos(viewOffset[0]+25, viewOffset[1]+25);
        HealthBar.setLoc(50, 635);
    }
}

void Game::decrementEnemy(int r)
{
    if (!running)
        return;

    enemysPerRoom[r]--;
    if (enemysPerRoom[r] <= 0)
    {
        if (currentRoom == 3) // to be fixed
            Win();
        else
        {
            doors[r][r+1]->unlock();
            doors[r+1][r]->unlock();
        }
    }
}

void Game::playerHealthChanged(float h)
{
    updatePlayerHealth(h);
}

Game::~Game() {}
