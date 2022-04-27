#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneEvent>
//#include <QGraphicsSceneMouseEvent>

#include <QGraphicsTextItem>

#include <QDebug>

class Button: public QObject, public QGraphicsRectItem {
    Q_OBJECT
private:
    QGraphicsTextItem* text;

public:
    Button(QString name, int size_w, int size_h, QGraphicsItem * parent=NULL);
    ~Button();
    void setText(QString txt);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();
};

#endif // BUTTON_H
