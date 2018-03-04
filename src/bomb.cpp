#include "bomb.h"
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QPropertyAnimation>
#include <QSound>

Bomb::Bomb(): instance(800), hasBombed(0), isInGun(0)
{
    connect(this, SIGNAL(wasCollided()), this, SLOT(dealColliding()));
}

//传入的x1，y1是圆心坐标
//半径我们给800,800×k就是x坐标
//只需要根据圆的方程求y就好了
void Bomb::fly()
{
    //使用一次方程
    //斜率由炮管传入
//    float x = 0.0;
//    float y = 0.0;

//    //暂时使用
//    qDebug() << "fly中kx,ky的值" << kx << ky;
//    qDebug() << "圆心坐标值" << x1 << y1;

//    y = y1 - qAbs(this->instance*ky);

//    if (kx == 0) {
//        x = qAbs(x1);
//    } else if (kx < 0) {
//        x = x1 - qAbs(800*kx);
//    } else if (kx > 0) {
//        x = x1 + qAbs(800*kx);
//    }

//    qDebug() << "ｙ的值" << y;
//    qDebug() << "炮弹初始坐标" << this->pos();
//    qDebug() << "炮弹终止坐标" << x << y;

    qDebug() << dstPos;

    QSound::play(":/sound/sound/fireSound.wav");

    QPropertyAnimation * animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(getFlySpeed());
    animation->setStartValue(this->pos());
    animation->setEndValue(this->dstPos);
    animation->start();

    connect(animation, SIGNAL(finished()), this, SLOT(deleteLater()));
}

QPointF Bomb::getDstPos() const
{
    return dstPos;
}

void Bomb::setDstPos(const QPointF &value)
{
    dstPos = value;
}

int Bomb::getHasBombed() const
{
    return hasBombed;
}

void Bomb::setHasBombed(int value)
{
    hasBombed = value;
}

int Bomb::getLife() const
{
    return life;
}

void Bomb::setLife(int value)
{
    life = value;
}

//威力大小
void Bomb::setPower(int value)
{
    power = value;
}

int Bomb::getPower() const
{
    return power;
}

int Bomb::getIsInGun() const
{
    return isInGun;
}

void Bomb::setIsInGun(int value)
{
    isInGun = value;
}

int Bomb::getShotSpeed() const
{
    return shotSpeed;
}

void Bomb::setShotSpeed(int value)
{
    shotSpeed = value;
}

int Bomb::getFlySpeed() const
{
    return flySpeed;
}

void Bomb::setFlySpeed(int value)
{
    flySpeed = value;
}

/*******************************碰撞检测*****************************/
bool Bomb::isColliding()
{
    //发生了碰撞
    if (this->collidingItems().count() > 0) {
        return true;
    }

    return false;

}

/******************************基本函数*****************************/
QRectF Bomb::boundingRect() const
{
    qreal penWidth = 1;

    return QRectF(-50 - penWidth/2, -50 - penWidth/2,
                  100 + penWidth, 100 + penWidth);
}


