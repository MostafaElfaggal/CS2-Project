#ifndef WINLOSE_STATUS_H
#define WINLOSE_STATUS_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>

class WinLose_Status : public QGraphicsRectItem
{
private:
    QGraphicsTextItem msg;

public:
    WinLose_Status();
    void init();

    void setLoc(float x_pos, float y_pos);

    void setMsg(QString m, float centerX, float centerY);

    void Show();
    void Hide();
};

#endif // WINLOSE_STATUS_H
