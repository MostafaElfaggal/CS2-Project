#include "shieldicon.h"

ShieldIcon::ShieldIcon(float x_pos, float y_pos) : GameObject(x_pos, y_pos, 40, 40, "ShieldIcon.png", "shield-icon")
{
    isVisible = false;
    running = false;
    setZValue(8);
    hide();
}

void ShieldIcon::start()
{
    isVisible = true;
    show();
    running = true;
    flickerCount = 0;
    startTimer(130);
}

void ShieldIcon::updateFrame(long long frame)
{
    if (!timer && running)
    {
        if (flickerCount != 8)
        {
            flicker();
            startTimer(10);
        } else {
            flicker();
            running = false;
        }
    }

    GameObject::updateFrame(frame);
}

void ShieldIcon::flicker()
{
    if (isVisible)
        hide();
    else
        show();
    isVisible = !isVisible;
    flickerCount++;
}
