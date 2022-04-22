#include "Button.h"
#include <QBrush>


Button::Button(QString name, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
    QGraphicsTextItem* text = new QGraphicsTextItem(name,this);
    int xpos=rect().width()/2 - text->boundingRect().width()/2;
    int ypos=rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xpos,ypos);
    setAcceptHoverEvents(true);
}