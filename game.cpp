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

#include "thunder.h"
#include "shieldtotem.h"

int Game::frame = 0;

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

int Game::adjust_to_borders(int i, int di)
{
    if (i+di >= 0 && i+di <=22)
        i += di;

    return i;

//    if (j+dj >= 0 && j+dj <= 22)
//        j+= dj;
}

Game::Game(QGraphicsView *v) : QGraphicsRectItem(QRect(0, 0, 1, 1)), pauseButton(25, 25, "pauseBtn.png", "pauseBtn-hover", "pauseBtn-pressed.png", 50, 50), HealthBar("health_bar", 50, 635), shield_icon(50+316+50, 650)
{
    p = new Player(0, 0);
    boss_died = false;
    purse = 0;

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("song.mp3"));
    audioOutput->setVolume(50);

    view = v;
    viewOffset[0] = 0;
    viewOffset[1] = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    connect(p, SIGNAL(callSwitchView(int)), this, SLOT(switchRoom(int)));

    bg.setPixmap(QPixmap("bg.png"));
    bg.setPos(viewOffset[0], viewOffset[1]);
    bg.setZValue(0);
}

void Game::init()
{
    enemysPerRoom[0] = 0;
    enemysPerRoom[1] = 0;
    enemysPerRoom[2] = 0;
    enemysPerRoom[3] = 0;

    loadWorld(); // enemies/blocks/walls/doors

    ///////////////////////////////////////////////////////////////////////////////////////// PLAYER
    p->setLoc(Pstart[0], Pstart[1]);
    p->loc[0] = Ploc[0];
    p->loc[1] = Ploc[1];
    scene()->addItem(p);
    p->init();
    p->setPtrs(&shield_icon);
    connect(p, SIGNAL(die(int)), this, SLOT(Lose()));
    connect(p, SIGNAL(changePurse(int)), this, SLOT(changePurse(int)));
//    connect(p, SIGNAL(changeHealth(float)), this, SLOT(playerHealthChanged(float)));
    /////////////////////////////////////////////////////////////////////////////////////////

    connect(boss, SIGNAL(boss_dying()), this, SLOT(handleBossDeath()));

    scene()->addItem(&status);
    status.init();

    scene()->addItem(&HealthBar);
    HealthBar.init();
    connect(p, SIGNAL(changeHealth(float)), &HealthBar, SLOT(updateValue(float)));

    scene()->addItem(&shield_icon);

    scene()->addItem(&pauseButton);
    connect(&pauseButton, SIGNAL(press()), this, SLOT(pauseMenu()));
    //    connect(&pauseButton,SIGNAL(resume()),this,SLOT(resume()));

    currentRoom = 0;
    running = false;

    scene()->addItem(&bg);
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
                //
                Ploc[0] = j;
                Ploc[1] = i;
            }
            else if (temp[0] == 'e')
            { // enemy1
                boarddata[i][j] = 1;
                Enemy* tmp;

                if (temp == "eS")
                {
                    tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i, room(j,i), "Skeleton", 3, j, i);
                } else if (temp == "eU")
                {
                    tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i, room(j,i), "UndeadKing", 3, j, i);
                } else if (temp == "ef")
                {
                    tmp = new Enemy2(offsetX + 50 * j, offsetY + 50 * i, room(j,i), "flying", 4, j, i);
                } else if (temp == "ec")
                {
                    tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i, room(j,i), "catBoss", 3, j, i);
                } else if (temp == "eB")
                {
                    tmp = new Enemy1(offsetX + 50 * j, offsetY + 50 * i, room(j,i), "BlackKnight", 3, j, i);
                }
                enemysPerRoom[room(j, i)]++;

                scene()->addItem(tmp);
                tmp->init();
                connect(tmp, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
            }
//            else if (temp == "e2")
//            { // enemy2
//                boarddata[i][j] = 1;
//                Enemy *tmp = new Enemy2(offsetX + 50 * j, offsetY + 50 * i, room(j,i));
//                enemysPerRoom[room(j, i)]++;

//                scene()->addItem(tmp);
//                tmp->init();
//                connect(tmp, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
//            }
            else if (temp == "bs")
            {
                boarddata[i][j] = 1;
                boss = new Boss(offsetX + 50 * j, offsetY + 50 * i, room(j,i), j, i);
                enemysPerRoom[room(j, i)]++;

                scene()->addItem(boss);
                boss->init();
                connect(boss, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
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
            } else if (temp == "hp")
            { // health potion
                boarddata[i][j] = 1;
                HealthPot *tmp = new HealthPot(offsetX + 50 * j, offsetY + 50 * i);
                scene()->addItem(tmp);
//                connect(tmp, SIGNAL(die(int)), this, SLOT(decrementEnemy(int)));
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

void Game::shortestPath()
{
    int g_table[BOARD_SIZE_H][BOARD_SIZE_W], prev[BOARD_SIZE_H][BOARD_SIZE_W][2];
    bool visited[BOARD_SIZE_H][BOARD_SIZE_W];

    for (int i=0; i<BOARD_SIZE_H; i++)
        for (int j=0; j<BOARD_SIZE_W; j++)
        {
        g_table[i][j] = -1;
        visited[i][j] = false;
        prev[i][j][0] = -1;
        prev[i][j][1] = -1;
        }

    int x_source = boss->loc[0];
    int y_source = boss->loc[1];

    int x_destination = p->loc[0];
    int y_destination = p->loc[1];

    if (x_destination == x_source && y_destination == y_source)
    {
        boss->x_next = x_source;
        boss->y_next = y_source;
        return;
    }

    g_table[y_source][x_source] = 0;

    int min_i=y_source, min_j=x_source;

    while(!visited[y_destination][x_destination])
    {
        for (int i=0; i<BOARD_SIZE_H; i++) // find minimum f to traverse
            for (int j=0; j<BOARD_SIZE_W; j++)
                if (!visited[i][j] && g_table[i][j] != -1 && (g_table[i][j]+abs(y_destination-i)+abs(x_destination-j) <= g_table[min_i][min_j]+abs(y_destination-min_i)+abs(x_destination-min_j) || visited[min_i][min_j]))
                {
                    min_i = i;
                    min_j = j;
                }

        visited[min_i][min_j] = true;
        int tmp_i, tmp_j;

        // up
        tmp_i = adjust_to_borders(min_i, -1);
        tmp_j = min_j;
        if (!visited[tmp_i][tmp_j] && (boarddata[tmp_i][tmp_j] > 0 || boarddata[tmp_i][tmp_j] == -3) && (g_table[tmp_i][tmp_j] > g_table[min_i][min_j]+1 || g_table[tmp_i][tmp_j] == -1)) // new node && not wall && more optimal
        {
            g_table[tmp_i][tmp_j] = g_table[min_i][min_j]+1; // weight distance one from any node to another neighbour
            prev[tmp_i][tmp_j][0] = min_i;
            prev[tmp_i][tmp_j][1] = min_j;
        }

        // down
        tmp_i = adjust_to_borders(min_i, 1);
        tmp_j = min_j;
        if (!visited[tmp_i][tmp_j] && (boarddata[tmp_i][tmp_j] > 0 || boarddata[tmp_i][tmp_j] == -3) && (g_table[tmp_i][tmp_j] > g_table[min_i][min_j]+1 || g_table[tmp_i][tmp_j] == -1)) // new node && not wall && more optimal
        {
            g_table[tmp_i][tmp_j] = g_table[min_i][min_j]+1; // weight distance one from any node to another neighbour
            prev[tmp_i][tmp_j][0] = min_i;
            prev[tmp_i][tmp_j][1] = min_j;
        }

        // right
        tmp_i = min_i;
        tmp_j = adjust_to_borders(min_j, 1);
        if (!visited[tmp_i][tmp_j] && (boarddata[tmp_i][tmp_j] > 0 || boarddata[tmp_i][tmp_j] == -3) && (g_table[tmp_i][tmp_j] > g_table[min_i][min_j]+1 || g_table[tmp_i][tmp_j] == -1)) // new node && not wall && more optimal
        {
            g_table[tmp_i][tmp_j] = g_table[min_i][min_j]+1; // weight distance one from any node to another neighbour
            prev[tmp_i][tmp_j][0] = min_i;
            prev[tmp_i][tmp_j][1] = min_j;
        }

        // left
        tmp_i = min_i;
        tmp_j = adjust_to_borders(min_j, -1);
        if (!visited[tmp_i][tmp_j] && (boarddata[tmp_i][tmp_j] > 0 || boarddata[tmp_i][tmp_j] == -3) && (g_table[tmp_i][tmp_j] > g_table[min_i][min_j]+1 || g_table[tmp_i][tmp_j] == -1)) // new node && not wall && more optimal
        {
            g_table[tmp_i][tmp_j] = g_table[min_i][min_j]+1; // weight distance one from any node to another neighbour
            prev[tmp_i][tmp_j][0] = min_i;
            prev[tmp_i][tmp_j][1] = min_j;
        }
    }

    int tmp_i = y_destination, tmp_j = x_destination;
    int temp;
    while (!(prev[tmp_i][tmp_j][0] == y_source && prev[tmp_i][tmp_j][1] == x_source))
    {
        temp = prev[tmp_i][tmp_j][0];
        tmp_j = prev[tmp_i][tmp_j][1];
        tmp_i = temp;
    }

    boss->x_next = tmp_j;
    boss->y_next = tmp_i;
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
    frame %= MAX_FRAME;

    shortestPath();

    QList<QGraphicsItem*> items = scene()->items();

    QList<QGraphicsItem*>::iterator i;
    for (i = items.begin(); i != items.end() && running; ++i)
    {
        if (!(*i))
            continue;
        GameObject* itemptr = dynamic_cast<GameObject*>(*i);
        if (itemptr)
            itemptr->updateFrame(frame);
    }

    // Thunder
    if (frame%300 == 0) // 10 seconds
    {
        QVector<int> i, j;
        int subI, subJ;
        for (int _=0; _<3; _++) // 3 bolts at a time
        {
            subI = rand()%8+14;
            subJ = rand()%8+1;
            while(boarddata[subI][subJ] < 0 || i.indexOf(subI) != -1 || j.indexOf(subJ) != -1) // to ensure no 2 bolts on same row or column
            {
                subI = rand()%8+14;
                subJ = rand()%8+1;
            }

            i.push_back(subI);
            j.push_back(subJ);
            Thunder* t = new Thunder(offsetX + 50 * subJ, offsetY + 50 * subI);
    //        Thunder* t = new Thunder(offsetX + 50 * 1, offsetY + 50 * 8);
    //        Thunder* t = new Thunder(125, 175);
            scene()->addItem(t);
        }
    }

    // Shield Totem
    if (frame%600 == 0) // 20 seconds
//    if (frame%300 == 0)
    {
        int i, j;
        i = rand()%8+14;
        j = rand()%8+1;
        while(boarddata[i][j] < 0)
        {
            i = rand()%8+14;
            j = rand()%8+1;
        }

        ShieldTotem* st = new ShieldTotem(offsetX + 50 * j, offsetY + 50 * i);
//        ShieldTotem* st = new ShieldTotem(offsetX + 50 * 1, offsetY + 50 * 8);
//        ShieldTotem* st = new ShieldTotem(125, 175);
        scene()->addItem(st);
    }

    scene()->update(0,0,1300,2100);
}

void Game::pauseMenu()
{
    if (!running)
        return;

    pause();
    showPauseMenu(1350/2+viewOffset[0]-540/2, 750/2+viewOffset[1]-400/2);
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
    p->ClearBullets(true);
    p->Hide();
    scene()->removeItem(p);

    // clearing enemy bullets
    QVector<Enemy*> es;
    QVector<QGraphicsItem*> gitms;
    QList<QGraphicsItem*> items = scene()->items();
    QList<QGraphicsItem*>::iterator i;
    for (i=items.begin(); i!=items.end(); i++)
    {
        Enemy* eptr = dynamic_cast<Enemy*>(*i);
        if (eptr)
            es.push_back(eptr);
    }

    for (auto i=es.begin(); i!=es.end(); ++i)
        (*i)->ClearBullets(true);

    // gameitems
    items = scene()->items();
    for (i=items.begin(); i!=items.end(); i++)
    {
        GameItem* giptr = dynamic_cast<GameItem*>(*i);
        if (giptr)
            gitms.push_back(*i);
    }
    for (auto i=gitms.begin(); i!=gitms.end(); ++i)
        delete (*i);

//    status.setMsg(QString("You Win!"), 1350/2+viewOffset[0], 750/2+viewOffset[1]);
    status.setCondition(true);
    status.setLoc(1350/2+viewOffset[0], 750/2+viewOffset[1]);
    status.Show();
}

void Game::Lose()
{
    if (!running)
        return;
    pause();
    musicOff();
    p->blockBullets();
    p->ClearBullets(true);
    p = NULL;

    // clearing enemy bullets and deleting enemies
    QVector<Enemy*> es;
    QVector<QGraphicsItem*> gitms;
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
        (*i)->ClearBullets(true);
        delete (*i);
    }

    // gameitems
    items = scene()->items();
    for (i=items.begin(); i!=items.end(); i++)
    {
        GameItem* giptr = dynamic_cast<GameItem*>(*i);
        if (giptr)
            gitms.push_back(*i);
    }
    for (auto i=gitms.begin(); i!=gitms.end(); ++i)
        delete (*i);

    status.setCondition(false);
    status.setLoc(1350/2+viewOffset[0], 750/2+viewOffset[1]);
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
        pauseButton.setLoc(viewOffset[0]+25, viewOffset[1]+25);
        HealthBar.setLoc(50, viewOffset[1]+662.5);
        shield_icon.setLoc(50+316+50, viewOffset[1] + 675);

        bg.setPos(viewOffset[0], viewOffset[1]);
    }
    else if (newRoom == 2 && fromRoom == 1)
    {
        view->setSceneRect(0, 0, 1300, 750);
        viewOffset[0] = 0;
        viewOffset[1] = 0;
        pauseButton.setLoc(viewOffset[0]+25, viewOffset[1]+25);
        HealthBar.setLoc(50, 635);
        shield_icon.setLoc(50+316+50, 650);

        bg.setPos(viewOffset[0], viewOffset[1]);
    }
}

void Game::decrementEnemy(int r)
{
    if (!running)
        return;

    enemysPerRoom[r]--;
    if (enemysPerRoom[r] <= 0)
    {
//        if (currentRoom == 3) // to be fixed
        if (boss_died)
            Win();
        else
        {
            doors[r][r+1]->unlock();
            doors[r+1][r]->unlock();
        }
    }
}

void Game::handleBossDeath()
{
    boss_died = true;
}

void Game::playerHealthChanged(float h)
{
    updatePlayerHealth(h);
}

void Game::changePurse(int x)
{
    purse += x;
}

Game::~Game() {}
