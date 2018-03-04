#ifndef CIRCLEBOMB_H
#define CIRCLEBOMB_H

#include "bomb.h"

//三角形炮弹，继承自炮弹

class CircleBomb : public Bomb
{
public:
    CircleBomb(QPointF point);

    //构造函数初始化炮弹的一些基本属性
    //起始也不一定需要，因为通过setget函数可以进行设置

    //绘制圆形的炮弹
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    //碰撞检测
    //确定引爆范围
    QPainterPath shape() const;
    void bombEffect();

public slots:
    void dealColliding();

private:
};

#endif // CIRCLEBOMB_H
