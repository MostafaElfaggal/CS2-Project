#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "menu.h"


class PauseMenu : public Menu
{
    Q_OBJECT
public:
    PauseMenu(Game* g);

public slots:
    void btn1();
    void Show(float x_pos, float y_pos);
    void Hide();
};

#endif // PAUSEMENU_H
