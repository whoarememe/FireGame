#include "gun.h"
#include "bomb.h"
#include "circlebomb.h"
#include "trianglebomb.h"
#include "squarebomb.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include <QToolTip>
#include <QGraphicsScene>
#include <QtMath>
#include <QSound>

Gun::Gun()
{
    //装弹准备
    ready(bomb, "squareTower");
}

Gun::Gun(Bomb * bomb, int speed): rotationItem(0),
    life(-1), power(-1)
{
    setFlag(QGraphicsObject::ItemIsFocusable);

    oldTransform = transform();

    this->bomb = bomb;
    //初始化为方块炮弹
    this->flyBomb = new SquareBomb(QPointF(0, 0));
    this->speed = speed;

    gunSender = new QUdpSocket(this);

    //装弹准备
    ready(bomb, "squareTower");
}

/*********************装弹函数**************************/
void Gun::ready(Bomb * bomb, QString str)
{
    //装弹声音
    QSound::play(":/sound/sound/shangtang.wav");

    this->str = str;

    //生成一个用于飞行的炮弹来代替炮管中的炮弹
    Bomb * flyBomb;

    if (str == "triangleTower") {
        flyBomb = new TriangleBomb(QPointF(0,0));
        flyBomb->setLife(10);
    } else if (str == "squareTower") {
        flyBomb = new SquareBomb(QPointF(0,0));
        flyBomb->setLife(20);
    } else if (str == "circleTower") {
        flyBomb = new CircleBomb(QPointF(0,0));
        flyBomb->setLife(40);
    } else {
        ;
    }

    this->flyBomb = flyBomb;

    this->bomb->setIsInGun(1);
    //将在弹堂里面的子弹添加到炮管
    this->bomb->setParentItem(this);

    QPropertyAnimation * animation =
            new QPropertyAnimation(bomb, "pos");
    animation->setDuration(this->bomb->getShotSpeed());
    animation->setStartValue(QPoint(0, 0));
    animation->setEndValue(QPoint(0, -55));
    animation->start();

    //发射装弹完毕信号
    connect(animation, SIGNAL(finished()), this, SLOT(emitFinishShot()));
}

//发射装弹完毕信号
void Gun::emitFinishShot()
{
    emit finishShot();
}

/*********************炮塔改变**************************/
void Gun::towerChanged(Bomb * bomb, int speed, QString str)
{
    this->bomb->deleteLater();
    this->bomb = bomb;
    this->speed = speed;

    ready(bomb, str);
}

int Gun::getLife() const
{
    return life;
}

void Gun::setLife(int value)
{
    life = value;
}

/*********************开火函数**************************/
void Gun::fire()
{  
    //弹道计算
    float kx = 0.0;
    float ky = 0.0;

    float x = 0.0;
    float y = 0.0;

    QPointF scenePosBomb = this->mapToScene(this->bomb->pos() - QPointF(0, 20));
    QPointF scenePosCircle = this->mapToScene(QPointF(0, 0));

    //长度就是55,炮管的长度
//    qDebug() << "炮管中炮弹坐标" << this->bomb->pos();
//    qDebug() << "炮管中的kx ky值" << kx, ky;
//    qDebug() << "scenePosBomb" << scenePosBomb;
//    qDebug() << "scenePosCircle" << scenePosCircle;

    kx = (scenePosBomb.x() - scenePosCircle.x())/(QPointF(0, 0) - this->bomb->pos() + QPointF(0, 20)).y();
    ky = (scenePosBomb.y() - scenePosCircle.y())/(QPointF(0, 0) - this->bomb->pos() + QPointF(0, 20)).y();

    this->bomb->deleteLater();

    //计算终止坐标
    y = scenePosCircle.y() - qAbs(800*ky);

    //暂时使用
//    qDebug() << "fly中kx,ky的值" << kx << ky;

    if (kx == 0) {
        x = qAbs(scenePosCircle.x());
    } else if (kx < 0) {
        x = scenePosCircle.x() - qAbs(800*kx);
    } else if (kx > 0) {
        x = scenePosCircle.x() + qAbs(800*kx);
    }

    //起始坐标与终止坐标
    scene()->addItem(flyBomb);
    flyBomb->setPos(scenePosBomb);
    flyBomb->setDstPos(QPointF(x, y));
    //炮弹发射    
    flyBomb->fly();

    emit hasShot();

    //发送开火的一些信息
    QByteArray datagram;
    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&datagram, QIODevice::WriteOnly);
    //代表发射炮弹，什么类型的炮弹,初始位置， 终止位置, feixing速度
    out << fireBomb << this->str << scenePosBomb << QPointF(x, y) << flyBomb->getFlySpeed();
    gunSender->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 8888);

}

/*********************炮管的绘制**************************/
QRectF Gun::boundingRect() const
{
    qreal penWidth = 1;

    return QRectF(-7.5 - penWidth/2, -60 - penWidth/2,
                  15 + penWidth, 80 + penWidth);
}

void Gun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(-7.5, -60.5, 15, 80);
    painter->drawEllipse(0, 0, 2, 2);
}

QPainterPath Gun::shape() const
{
    QPainterPath path;
    path.addRect(-2, -2, 4, 4);
    return path;
}

/*********************炮塔旋转**************************/
void Gun::turnToLeft()
{
    oldTransform.rotate(-1);
    rotationItem -= 1;
    if (rotationItem < -70 || rotationItem > 70) {
        oldTransform.rotate(1);
        rotationItem += 1;
    } else {
        /*****************************网络**************************/
        QByteArray datagram;

        //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
        QDataStream out(&datagram, QIODevice::WriteOnly);
        //代表炮塔旋转，旋转方向, rotationItem,起始代表旋转一次就是一个角度，发送的rotation
        //是代表看看是不是角度匹配
        out << rotateGun << tr("left") << rotationItem;
        gunSender->writeDatagram(datagram.data(), datagram.size(),
                                 QHostAddress::Broadcast, 8888);
    }

    setTransform(oldTransform);
}

void Gun::turnToRight()
{
    oldTransform.rotate(1);
    rotationItem += 1;
    if (rotationItem < -70 || rotationItem > 70) {
        oldTransform.rotate(-1);
        rotationItem -= 1;
    } else {
        /*****************************网络**************************/
        QByteArray datagram;

        //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
        QDataStream out(&datagram, QIODevice::WriteOnly);
        //代表炮塔旋转，旋转方向, rotationItem,起始代表旋转一次就是一个角度，发送的rotation
        //是代表看看是不是角度匹配
        out << rotateGun << tr("right") << rotationItem;
        gunSender->writeDatagram(datagram.data(), datagram.size(),
                                 QHostAddress::Broadcast, 8888);
    }

    setTransform(oldTransform);

}

/*********************get和set**************************/
QTransform Gun::getOldTransform() const
{
    return oldTransform;
}

void Gun::setOldTransform(const QTransform &value)
{
    oldTransform = value;
}
