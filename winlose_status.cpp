#include "winlose_status.h"


WinLose_Status::WinLose_Status()
{
//    QFont titleFont("Comic Sans",80);
//    msg.setFont(titleFont);

    prepareGeometryChange();
    setPos(0, 0);
//    setBrush(QBrush(Qt::blue));
    setZValue(13);


    setCondition(true);
//    setMsg(QString("You Win!"), 300, 300);
//    msg.setZValue(14);

    Hide();
}

void WinLose_Status::init()
{
//    scene()->addItem(&msg);
}

void WinLose_Status::setLoc(float x_pos, float y_pos)
{
//    float wm=msg.boundingRect().width(), hm=msg.boundingRect().height();
    float w=boundingRect().width(), h=boundingRect().height();

    prepareGeometryChange();
    setPos(x_pos-w/2, y_pos-h/2);

//    msg.setPos(x_pos-wm/2,y_pos-hm/2);
}

//void WinLose_Status::setMsg(QString m, float centerX, float centerY)
//{
//    msg.setPlainText(m);

//    float wm=msg.boundingRect().width(), hm=msg.boundingRect().height();
//    setRect(QRect(0, 0, wm+20, hm+20));

//    float w=boundingRect().width(), h=boundingRect().height();
//    setLoc(centerX, centerY);
//}

void WinLose_Status::setCondition(bool isWin) {
    if (isWin)
        setPixmap(QPixmap("Win Message.png"));
    else
        setPixmap(QPixmap("Lose Message.png"));
}

void WinLose_Status::Show()
{
    show();
//    msg.show();


    setZValue(200);
//    msg.setZValue(201);
}

void WinLose_Status::Hide()
{
    hide();
//    msg.hide();
}
