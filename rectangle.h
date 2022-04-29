#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsRectItem>

class Rectangle : public QGraphicsRectItem
{
public:
    Rectangle();
    void setRect(QRect);
    void setLoc(float x_pos, float y_pos);
};

#endif // RECTANGLE_H
