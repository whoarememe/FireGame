#ifndef SQUAREBOMB_H
#define SQUAREBOMB_H

#include "bomb.h"

class SquareBomb : public Bomb
{
public:
    SquareBomb(QPointF point);

    //绘制圆形的炮弹
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    //碰撞检测
    //确定引爆范围
    QPainterPath shape() const;

    void bombEffect();

public slots:
    void dealColliding();
};

#endif // SQUAREBOMB_H
