#ifndef EXPLODE_H
#define EXPLODE_H

#include <QGraphicsItem>
#include <QSound>

class explode : public QGraphicsObject
{
    Q_OBJECT

public:
    explode(int i);

    //爆炸图形项
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    //尽可能的小
    QPainterPath shape() const;

private slots:
    void deleteThis();

private:
    int i;

};

#endif // EXPLODE_H
