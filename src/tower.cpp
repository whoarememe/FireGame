#include "tower.h"

#include <QTimer>
#include <QPainter>
#include <QDebug>


Tower::Tower(): power(-1)
{
    currentPos = this->pos();
    qDebug() << "我是塔， 我的坐标是" << this->pos();
    //默认为浅红色
    this->towerColor = QColor(247, 75, 83, 255);
    //生命值初始化为100
    life = 100;
    //炮弹数量初始化为100
    numBom = 100;

    resumeAppear();
}

QRectF Tower::boundingRect() const
{
    //炮塔就用50X50吧
    qreal penWidth = 1;

    return QRectF(-40 - penWidth/2, -40 - penWidth/2,
                  80 + penWidth, 80 + penWidth);

}

QColor Tower::getTowerColor() const
{
    return towerColor;
}

void Tower::setTowerColor(const QColor &value)
{
    towerColor = value;
}

int Tower::getNumBom() const
{
    return numBom;
}

void Tower::setNumBom(int value)
{
    numBom = value;
}

int Tower::getLife() const
{
    return life;
}

void Tower::setLife(int value)
{
    life = value;
}

bool Tower::isColliding()
{
    if (this->collidingItems().count() > 1) {
        return true;
    }

    return false;
}

void Tower::isSolliding()
{
    emit wasAttacked();

}

void Tower::changNum()
{
    QRectF rect(-25, -25, 50, 50);
//    painter->setPen(QColor(0, 0, 0));
//    painter->drawText(rect, Qt::AlignHCenter, QString::number(this->getNumBom()));
    qDebug() << this->getNumBom();
}

void Tower::changeAppear(QColor color)
{
    qDebug() << "i am here";
    if (this->life > 0) {

        dropEffect->setColor(color);
        dropEffect->setBlurRadius(50);
        dropEffect->setOffset(0);
        setGraphicsEffect(dropEffect);

        QTimer::singleShot(200, this, SLOT(resumeAppear()));

        animation = new QPropertyAnimation(this, "pos");
        animation->setDuration(200);
        animation->setKeyValueAt(0.2, (this->pos() - QPoint(2, 2)));
        animation->setKeyValueAt(0.4, (this->pos() - QPoint(-2, -2)));
        animation->setKeyValueAt(0.6, (this->pos() - QPoint(2, 2)));
        animation->setKeyValueAt(0.8, (this->pos() - QPoint(-2, -2)));
        animation->setKeyValueAt(0.9, (this->pos() - QPoint(2, 2)));
        animation->setKeyValueAt(1.0, (this->pos() - QPoint(-2, -2)));
        animation->start();
    }
}

void Tower::towerWasAttackSound()
{
    QSound::play(":/sound/sound/tower_was_attacked.wav");
}

void Tower::resumeAppear()
{
    //当有生命值的时候
    if (life > 0) {
        //默认效果
        dropEffect->setColor(QColor(0, 55, 255, 150));
        dropEffect->setBlurRadius(50);
        dropEffect->setOffset(0);
        setGraphicsEffect(dropEffect);
    } else {
        colorEffect->setColor(QColor(0, 0, 0, 150));
        colorEffect->setStrength(0.6);
        graphicsEffect()->setEnabled(false);
        setGraphicsEffect(colorEffect);
    }
//    this->setPos(currentPos);
    qDebug() << "我是塔， 我的坐标是" << this->pos() << currentPos;
}

QPainter *Tower::getPainter() const
{
    return painter;
}

void Tower::setPainter(QPainter *value)
{
    painter = value;
}


