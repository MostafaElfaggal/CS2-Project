#include "gameobject.h"

#include "game.h"

GameObject::GameObject(float x_pos, float y_pos, int size_w, int size_h, QString img_file, QString item)
{
    prepareGeometryChange();
    setImage(size_w, size_h, img_file);
    setPos(x_pos, y_pos);

    setZValue(0);

    itm = item;
}

void GameObject::init()
{

}

void GameObject::setImage(int size_w, int size_h, QString img_file)
{
    QPixmap img(img_file);
    img = img.scaledToWidth(size_w);
    img = img.scaledToHeight(size_h);
    setPixmap(img);
}

void GameObject::animate() {
    setPixmap(animations->at(current_animations++));
    current_animations %= animations->size();
}

void GameObject::updateFrame(long long frame) {
    if (timer && (((frame-timerStart)%MAX_FRAME)+MAX_FRAME)%MAX_FRAME == timerDuration)
        timer = false;
}

void GameObject::setLoc(float x_pos, float y_pos)
{
    prepareGeometryChange();
    setPos(x_pos, y_pos);
    QGraphicsItem::update();
}

void GameObject::startTimer(long long durationFrames)
{
    timerStart = Game::frame;
    timerDuration = durationFrames;
    timer = true;
}
