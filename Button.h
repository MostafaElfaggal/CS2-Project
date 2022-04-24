#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

class Button: public QObject, public QGraphicsRectItem {
    Q_OBJECT
private:
    QGraphicsTextItem* text;

public:
    Button(QString name,QGraphicsItem * parent=NULL);
    void setText(QString txt);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();
};

#endif // BUTTON_H
