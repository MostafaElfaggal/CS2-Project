#include "clickableimage.h"

ClickableImage::ClickableImage(float x_pos, float y_pos, QString normal, QString hover, QString pressed, int size_w, int size_h, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), normal_img(normal), hover_img(hover), pressed_img(pressed)
{
    prepareGeometryChange();

    normal_img.scaledToWidth(size_w);
    normal_img.scaledToHeight(size_h);

    hover_img.scaledToWidth(size_w);
    hover_img.scaledToHeight(size_h);

    pressed_img.scaledToWidth(size_w);
    pressed_img.scaledToHeight(size_h);

    setPixmap(normal_img);
    setLoc(x_pos, y_pos);

    setAcceptHoverEvents(true);

    setZValue(10);
}

void ClickableImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(pressed_img);
}

void ClickableImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(normal_img);
    press();
}

void ClickableImage::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(hover_img);
}

void ClickableImage::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(normal_img);
}

void ClickableImage::setLoc(float x_pos, float y_pos)
{
    prepareGeometryChange();
    setPos(x_pos, y_pos);
}
