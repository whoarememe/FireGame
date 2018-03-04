#ifndef SQUARETOWER_H
#define SQUARETOWER_H

#include "tower.h"

#include <QGraphicsObject>

class SquareTower : public Tower
{
    Q_OBJECT

public:
    SquareTower();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    QPainterPath shape() const;

private slots:
    //处理撞击
    void dealColliding();
};

#endif // SQUARETOWER_H
