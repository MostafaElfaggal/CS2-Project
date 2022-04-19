#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>

class WorldObject : public QObject, public QGraphicsPixmapItem
{
public:
    WorldObject(int x_pos, int y_pos, int size_w, int size_h, QString img_file);
};

#endif // WORLDOBJECT_H
