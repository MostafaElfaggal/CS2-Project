#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>

enum direction {
    UP, DOWN, RIGHT, LEFT, NONE
};


class GameObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    long long timerStart, timerDuration;

protected:
    int current_animations = 0;
    bool timer;

public:
    QString itm;

    QVector<QPixmap>* animations;
    GameObject(float x_pos, float y_pos, int size_w, int size_h, QString img_file, QString item);
    virtual void init();
    void setImage(int size_w, int size_h, QString img_file);
    void animate(); // use the animate function every x frames which will auto scroll through the different animations
    virtual void updateFrame(long long frame);
    void setLoc(float x_pos, float y_pos);

    void startTimer(long long durationFrames);
};

#endif // GAMEOBJECT_H
