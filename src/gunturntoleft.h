#ifndef GUNTURNTOLEFT_H
#define GUNTURNTOLEFT_H

#include <QGraphicsObject>

class GunTurnToLeft : public QGraphicsObject
{
    Q_OBJECT
public:
    GunTurnToLeft();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
};

#endif // GUNTURNTOLEFT_H
