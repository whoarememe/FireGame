#include "circletower.h"

#include <QPainter>
#include <QGraphicsEffect>

CircleTower::CircleTower()
{
    //圆形炮塔存储的弹药数量是30个
    this->setNumBom(30);
    //圆形炮塔的生命值是100
    this->setLife(100);
}

void CircleTower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    this->setPainter(painter);
    //添加碰撞效果
    if (this->collidingItems().count() > 0) {
        emit wasAttacked();
    }

    painter->setPen(this->getTowerColor());
    painter->setBrush(this->getTowerColor());

    painter->drawEllipse(-40, -40, 80, 80);

}

QPainterPath CircleTower::shape() const
{
    QPainterPath path;
    path.addEllipse(-40, -40, 80, 80);

    return path;

}

