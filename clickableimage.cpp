#include "clickableimage.h"

ClickableImage::ClickableImage(float x_pos, float y_pos, QString normal, QString hover, QString pressed, int size_w, int size_h, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), normal_img(normal), hover_img(hover), pressed_img(pressed)
{
    prepareGeometryChange();

    normal_img = normal_img.scaledToWidth(size_w);
    normal_img = normal_img.scaledToHeight(size_h);

    hover_img = hover_img.scaledToWidth(size_w);
    hover_img = hover_img.scaledToHeight(size_h);

    pressed_img = pressed_img.scaledToWidth(size_w);
    pressed_img = pressed_img.scaledToHeight(size_h);

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

void ClickableImage::setImage(QString img_normal, QString img_hover, QString img_pressed, int size_w, int size_h)
{
    normal_img = QPixmap(img_normal);
    hover_img = QPixmap(img_hover);
    pressed_img = QPixmap(img_pressed);

    normal_img = normal_img.scaledToWidth(size_w);
    normal_img = normal_img.scaledToHeight(size_h);

    hover_img = hover_img.scaledToWidth(size_w);
    hover_img = hover_img.scaledToHeight(size_h);

    pressed_img = pressed_img.scaledToWidth(size_w);
    pressed_img = pressed_img.scaledToHeight(size_h);

}
