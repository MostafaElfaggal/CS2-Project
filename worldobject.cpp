#include "worldobject.h"

WorldObject::WorldObject(int x_pos, int y_pos, int size_w, int size_h, QString img_file)
{
    QPixmap img(img_file);
    img = img.scaledToWidth(size_w);
    img = img.scaledToHeight(size_h);
    setPixmap(img);
    setPos(x_pos, y_pos);
}
