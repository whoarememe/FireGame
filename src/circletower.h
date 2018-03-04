#ifndef CIRCLETOWER_H
#define CIRCLETOWER_H

#include "tower.h"
#include <QGraphicsObject>

class CircleTower : public Tower
{
    Q_OBJECT

public:
    CircleTower();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    QPainterPath shape() const;
};

#endif // CIRCLETOWER_H
