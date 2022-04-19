#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>

enum direction {
    UP, DOWN, RIGHT, LEFT
};


class GameObject : public QObject, public QGraphicsPixmapItem
{
public:
    GameObject(int x_pos, int y_pos, int size_w, int size_h, QString img_file);
    virtual void update(int frame);
};

#endif // GAMEOBJECT_H
