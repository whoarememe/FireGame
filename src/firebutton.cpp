#include "firebutton.h"
#include <QPainter>
#include <QEvent>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QGraphicsScene>

FireButton::FireButton()
{
    setFlag(QGraphicsObject::ItemIsFocusable);

//    QKeyEvent myevent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
//    qApp->sendEvent(scene(), &myevent);
}

/*****************************************基本绘制****************************************/
QRectF FireButton::boundingRect() const
{
    qreal penwidth = 1;

    return QRectF(-25 - penwidth/2, -25 - penwidth/2,
                  50 + penwidth, 50 + penwidth);

}

void FireButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/skill/pic/texiaozu/fire.png");

    painter->drawPixmap(-pixmap.width()/2, -pixmap.height()/2, pixmap);
}

/******************************各种事件******************************************/
void FireButton::mousePressEvent(QMouseEvent *event)
{
//    QKeyEvent fireEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);

    if (event->button() == Qt::LeftButton) {
        qDebug() << "i will fire";
    } else {
        qDebug() << "else zhongde";
    }

}

