#include "gunturntoright.h"

#include <QPainter>

GunTurnToRight::GunTurnToRight()
{

}

QRectF GunTurnToRight::boundingRect() const
{
    qreal penwidth = 1;

    return QRectF(-25 - penwidth/2, -25 - penwidth/2,
                  50 + penwidth, 50 + penwidth);
}

void GunTurnToRight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/skill/pic/texiaozu/right.png");

    painter->drawPixmap(-pixmap.width()/2, -pixmap.height()/2, pixmap);
}
