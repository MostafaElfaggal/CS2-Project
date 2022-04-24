#include "door.h"

Door::Door(int x_pos, int y_pos, int f, int t, bool isOpen) : GameObject(x_pos, y_pos, 50, 50, "Door.png")
{
    open = isOpen;
    from = f;
    to = t;

    if (open)
        unlock();
}

void Door::unlock()
{
    open = true;
    setPixmap(QPixmap("DoorUnlocked.png"));
}
