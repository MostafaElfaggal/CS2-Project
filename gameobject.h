#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>

enum direction {
    UP, DOWN, RIGHT, LEFT
};


class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameObject();
    virtual void update() = 0;
};

#endif // GAMEOBJECT_H
