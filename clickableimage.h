#ifndef CLICKABLEIMAGE_H
#define CLICKABLEIMAGE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>
//#include <QGraphicsSceneMouseEvent>
//#include <QGraphicsSceneHoverEvent>


class ClickableImage : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QPixmap normal_img, hover_img, pressed_img;
public:
    ClickableImage(float x_pos, float y_pos, QString normal, QString hover, QString pressed, int size_w, int size_h, QGraphicsItem * parent=NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void press();
    void resume();
};

#endif // CLICKABLEIMAGE_H
