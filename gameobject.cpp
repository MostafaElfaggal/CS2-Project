#include "gameobject.h"

GameObject::GameObject(float x_pos, float y_pos, int size_w, int size_h, QString img_file, QString item)
{
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

void GameObject::update(int frame) {
}
