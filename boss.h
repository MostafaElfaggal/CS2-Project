#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

class Boss : public Enemy
{
    Q_OBJECT
private:
    QVector<QPixmap> as;
public:
    int x_next, y_next;

    Boss(float x_pos, float y_pos, int r, int x_loc, int y_loc);
    void updateFrame(long long frame);
    ~Boss();

signals:
    void boss_dying();
};

#endif // BOSS_H
