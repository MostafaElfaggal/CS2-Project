#ifndef BAR_H
#define BAR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class bar : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QGraphicsPixmapItem prog_bar[111];
public:
    bar(QString img_file, float x_pos, float y_pos);
    void init();
    void setLoc(float x_pos, float y_pos);
public slots:
    void updateValue(float v);
};

#endif // BAR_H
