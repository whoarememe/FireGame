#ifndef TRIANGLETOWER_H
#define TRIANGLETOWER_H

#include "tower.h"

#include <QGraphicsObject>

class TriangleTower : public Tower
{
public:
    TriangleTower();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    QPainterPath shape() const;

};

#endif // TRIANGLETOWER_H
