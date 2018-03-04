#include "squaretower.h"
#include "bomb.h"

#include <QPainter>

SquareTower::SquareTower()
{
    //方形炮塔存储的弹药数量是50个
    this->setNumBom(50);
    //方形炮塔的生命值是200
    this->setLife(200);
    connect(this, SIGNAL(wasAttacked()), this, SLOT(dealColliding()));
}

void SquareTower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    this->setPainter(painter);
    painter->setPen(this->getTowerColor());
    painter->setBrush(this->getTowerColor());

    painter->drawRect(-40, -40, 80, 80);
}

QPainterPath SquareTower::shape() const
{
    QPainterPath path;
    path.addRect(-40, -40, 80, 80);

    return path;

}

void SquareTower::dealColliding()
{
    //注意，判断所有与他相撞的事物的威力
    //然后将这些威力相加，生命值减去即可
    //一般塔和炮塔的威力为0
    int life = 0;
    QList<QGraphicsItem *> itemList = this->collidingItems();

    foreach (QGraphicsItem * item, itemList) {
        Bomb * bomb = (Bomb *) item;

        life += bomb->getPower();
//        qDebug() << "square tower was attacked";
    }

    this->setLife(this->getLife() - life);
}
