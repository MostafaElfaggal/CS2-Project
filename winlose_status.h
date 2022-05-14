#ifndef WINLOSE_STATUS_H
#define WINLOSE_STATUS_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>

class WinLose_Status : public QGraphicsPixmapItem
{
private:
//    QGraphicsTextItem msg;
    bool win_loss;

public:
    WinLose_Status();
    void init();

    void setLoc(float x_pos, float y_pos);

    void setMsg(QString m, float centerX, float centerY);
    void setCondition(bool);

    void Show();
    void Hide();
};

#endif // WINLOSE_STATUS_H
