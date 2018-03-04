#include "triangletower.h"

#include <QPainter>
#include <QDebug>

TriangleTower::TriangleTower()
{
    //三角形炮塔存储的弹药数量是100个
    this->setNumBom(100);
    //圆形炮塔的生命值是300
    this->setLife(300);
}

void TriangleTower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    this->setPainter(painter);

    painter->setPen(this->getTowerColor());
    painter->setBrush(this->getTowerColor());

    QPolygonF polygon;
    polygon << QPointF(-40, 40) << QPointF(0, -40)
            << QPointF(40, 40)  << QPointF(-40, 40);

    painter->drawPolygon(polygon);



    if (isColliding()) {
        qDebug() << "triangle tower was attacked";
    }

}

QPainterPath TriangleTower::shape() const
{
    QPolygonF polygon;
    polygon << QPointF(-40, 40) << QPointF(0, -40)
            << QPointF(40, 40)  << QPointF(-40, 40);

    QPainterPath path;
    path.addPolygon(polygon);

    return path;

}

