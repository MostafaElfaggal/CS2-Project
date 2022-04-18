#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT

public:
    Game();
//    ~Game();
public slots:
    void update();
};
#endif // GAME_H
