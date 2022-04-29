#include "bar.h"

bar::bar(QString img_file, float x_pos, float y_pos)
{
    QPixmap img(img_file);
    setPixmap(img);

    prog_bar[0].setPixmap(QPixmap("bar_left.png"));
    prog_bar[103].setPixmap(QPixmap("bar_right.png"));
    QPixmap mid("bar_mid.png");
    for (int i=1; i<103; i++)
        prog_bar[i].setPixmap(mid);

    setLoc(x_pos, y_pos);
}

void bar::init()
{
    for (int i=0; i<104; i++)
    {
        scene()->addItem(&prog_bar[i]);
        prog_bar[i].setZValue(9);
    }
}

void bar::setLoc(float x_pos, float y_pos)
{
    prepareGeometryChange();
    setPos(x_pos, y_pos);
    x_pos += 79;
    y_pos += 20;
    for (int i=0; i<104; i++)
        prog_bar[i].setPos(x_pos+i*2, y_pos);
}

void bar::updateValue(float v)
{
    v = 104*v/100;
    v = (int)v;
    if (v>100) v = 104;
    if (v<0) v=0;

    for (int i=0; i<v; i++)
        prog_bar[i].show();

    for (int i=v; i<104; i++)
        prog_bar[i].hide();
}
