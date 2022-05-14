#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "gameobject.h"

enum ItemType {
    PotHealth,
    ThunderStrike,
    FlameWisp,
    Shield_Totem,
    ShieldForceField
};

class GameItem : public GameObject
{
protected:
    QVector<QPixmap> as;

public:
    ItemType itype;
    bool effect;
    GameItem(float x_pos, float y_pos, QString img_file);
    virtual void updateFrame(long long frame);
    virtual void die();
    ~GameItem();
};

#endif // GAMEITEM_H
