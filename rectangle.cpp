#include "rectangle.h"

Rectangle::Rectangle()
{
}

void Rectangle::setRect(QRect r)
{
    prepareGeometryChange();
    QGraphicsRectItem::setRect(r);
}

void Rectangle::setLoc(float x_pos, float y_pos)
{
    prepareGeometryChange();
    setPos(x_pos, y_pos);
    QGraphicsItem::update();
}
