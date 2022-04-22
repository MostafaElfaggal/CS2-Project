#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector>
#include <QObject>
#include <QGraphicsPixmapItem>

enum direction {
    UP, DOWN, RIGHT, LEFT
};


class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int current_animations = 0;
public:
    QVector<QPixmap> animations;
    GameObject(float x_pos, float y_pos, int size_w, int size_h, QString img_file);
    void animate();
    virtual void update(int frame);
};

#endif // GAMEOBJECT_H
