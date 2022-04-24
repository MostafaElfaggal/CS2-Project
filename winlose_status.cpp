#include "winlose_status.h"


WinLose_Status::WinLose_Status()
{
    QFont titleFont("Comic Sans",80);
    msg.setFont(titleFont);

    setPos(0, 0);
    setBrush(QBrush(Qt::blue));

    setMsg(QString("You Win!"), 300, 300);

    Hide();
}

void WinLose_Status::init()
{
    scene()->addItem(&msg);
}

void WinLose_Status::setLoc(float x_pos, float y_pos)
{
    setPos(x_pos, y_pos);

    float wm=msg.boundingRect().width(), hm=msg.boundingRect().height();
    float w=boundingRect().width(), h=boundingRect().height();

    msg.setPos(x_pos+w/2-wm/2,y_pos+h/2-hm/2);
}

void WinLose_Status::setMsg(QString m, float centerX, float centerY)
{
    msg.setPlainText(m);

    float wm=msg.boundingRect().width(), hm=msg.boundingRect().height();
    setRect(QRect(0, 0, wm+20, hm+20));

    float w=boundingRect().width(), h=boundingRect().height();
    setLoc(centerX-w/2, centerY-h/2);
}

void WinLose_Status::Show()
{
    show();
    msg.show();
}

void WinLose_Status::Hide()
{
    hide();
    msg.hide();
}
