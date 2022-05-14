#include "gameitem.h"

GameItem::GameItem(float x_pos, float y_pos, QString img_file) : GameObject(x_pos, y_pos, 50, 50, img_file, "pickup")
{
    effect = true;
    animations = &as;
    setZValue(8);
}

void GameItem::updateFrame(long long frame)
{
    if (frame%3 == 0)
        animate();
}

void GameItem::die()
{

}

GameItem::~GameItem()
{
    scene()->removeItem(this);
}
