#include "explode.h"
#include <QPainter>
#include <QTimer>

explode::explode(int i)
{
    this->i = i;

    QTimer::singleShot(200, this, SLOT(deleteThis()));
}

QRectF explode::boundingRect() const
{
    qreal penWidth = 1;

    return QRectF(-50 - penWidth/2, -50 - penWidth/2,
                  100 + penWidth, 100 + penWidth);
}

void explode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget)
{
    QPixmap pixmap;

    switch (i) {
    case 1:
        pixmap.load(":/baozha/pic/baozha/bomb1.png");
    break;
    case 2:
        pixmap.load(":/baozha/pic/baozha/bomb2.png");
        break;
    case 3:
        pixmap.load(":/baozha/pic/baozha/bomb3.png");
        break;
    case 4:
        pixmap.load(":/baozha/pic/baozha/bomb4.png");
        break;
    default:
        pixmap.load(":/baozha/pic/baozha/bomb1.png");
        break;
    }

    painter->drawPixmap(-pixmap.width()/2,
                        -pixmap.height()/2,
                        pixmap);
}

QPainterPath explode::shape() const
{
    QPainterPath path;
    path.addRect(-2, -2, 4, 4);

    return path;
}

void explode::deleteThis()
{
    delete this;
}

