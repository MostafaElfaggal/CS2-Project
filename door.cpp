#include "door.h"

Door::Door(int x_pos, int y_pos, int f, int t) : GameObject(x_pos, y_pos, 50, 50, "door_closed.png", "door"), bg(x_pos, y_pos)
{
    open = false;
    current = 0;
    from = f;
    to = t;

    for (int i=0; i<14; i++)
    {
        as.push_back(QPixmap("door_anim_opening_f" + QString::number(i) + ".png"));
        as[i] = as[i].scaledToHeight(50);
        as[i] = as[i].scaledToWidth(50);
    }
    animations = &as;

    setZValue(3);

    if (open)
        unlock();
}

void Door::init()
{
    scene()->addItem(&bg);
}

void Door::updateFrame(long long frame)
{
    if (open && current < 14)
    {
        animate();
        current++;
    } else if (current == 14)
    {
//        QPixmap img("door_fullyopen.png");
        QPixmap img("Road.png");
        img = img.scaledToHeight(50);
        img = img.scaledToWidth(50);
        setPixmap(img);
        bg.hide();
        current++;
    }
}

void Door::unlock()
{
    open = true;
    current = 0;
//    setPixmap(QPixmap("DoorUnlocked.png"));
//    setPixmap(QPixmap("Road.png"));
}

Door::~Door()
{
    scene()->removeItem(&bg);
    scene()->removeItem(this);
}
