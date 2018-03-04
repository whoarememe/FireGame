#ifndef TRIANGLEBOMB_H
#define TRIANGLEBOMB_H

//三角形炮弹
#include "bomb.h"

class TriangleBomb : public Bomb
{
public:
    TriangleBomb(QPointF point);

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

#endif // TRIANGLEBOMB_H
