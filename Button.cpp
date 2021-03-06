#include "Button.h"
#include <QBrush>


Button::Button(QString name, int size_w, int size_h, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0,size_w,size_h);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
    setZValue(11);

    text = new QGraphicsTextItem(name,this);
    int xpos=rect().width()/2 - text->boundingRect().width()/2;
    int ypos=rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xpos,ypos);
    text->setZValue(12);

    setAcceptHoverEvents(true);
}

Button::~Button()
{
}

void Button::setText(QString txt)
{
    text->setPlainText(txt);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "pressed";
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "released";
    clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug() << "in";
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //    qDebug() << "out";
}

void Button::setLoc(float x_pos, float y_pos)
{
    prepareGeometryChange();
    setPos(x_pos, y_pos);
}
