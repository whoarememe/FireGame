#include "towergroup.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <typeinfo>

#include "bomb.h"
#include "squarebomb.h"
#include "circlebomb.h"
#include "trianglebomb.h"

TowerGroup::TowerGroup(): shotFlag(1)
{
    setFlag(QGraphicsObject::ItemIsFocusable);
    setFocus();

    groupTowerSocket = new QUdpSocket(this);

    //切换速度
    speed = 500;

    /******************炮塔和炮管的属性*************************/
    /***炮塔***/
    circleTower = new CircleTower;
    triangleTower = new TriangleTower;
    squareTower = new SquareTower;
    //设置炮塔生命值
    circleTower->setLife(300);
    squareTower->setLife(200);
    triangleTower->setLife(100);
    //为炮塔装弹
    circleTower->setNumBom(2);
    squareTower->setNumBom(50);
    triangleTower->setNumBom(100);

    /***炸弹***/
    //炸弹
    circleBomb = new CircleBomb(QPointF(0, 0));
    squareBomb = new SquareBomb(QPointF(0, 0));
    triangleBomb = new TriangleBomb(QPointF(0, 0));

    /***枪***/
    gun = new Gun(squareBomb, speed);

    /******************炮塔安装到战场***************************/
    addToGroup(circleTower);
    addToGroup(triangleTower);
    addToGroup(squareTower);
    addToGroup(gun);

    triangleTower->setPos(-185, 0);
    squareTower->setPos(0, 0);
    circleTower->setPos(185, 0);
    gun->setPos(0, -20);

    /*******************炮塔组的基本设置 ************************/
    currentTower = squareTower;
    currentId = 1;

    towerList << triangleTower << squareTower << circleTower;
    strList << "triangleTower" << "squareTower" << "circleTower";

    mapTowerBomb.insert(circleTower, circleBomb);
    mapTowerBomb.insert(triangleTower, triangleBomb);
    mapTowerBomb.insert(squareTower, squareBomb);

    /**********************控制组**************************/
    fireButton = new FireButton();
    gunTurnToLeft = new GunTurnToLeft();
    gunTurnToRight = new GunTurnToRight();

    addToGroup(fireButton);
    addToGroup(gunTurnToLeft);
    addToGroup(gunTurnToRight);
    fireButton->setPos(0, 75);
    gunTurnToLeft->setPos(-60, 75);
    gunTurnToRight->setPos(60, 75);

    /**********************信号组**************************/
    connect(this, SIGNAL(towerChanged(Bomb*, int, QString)),
            gun, SLOT(towerChanged(Bomb*, int, QString)));

    connect(gun, SIGNAL(finishShot()), this, SLOT(zhuangdanwanbi()));

    readyShot();
}

bool TowerGroup::isColling()
{
    QList<QGraphicsItem *> itemList = childItems();

    QGraphicsItem * item;
    //没有发生碰撞
    return false;
}

void TowerGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pGroup = event->pos();

    this->gun->setFocus();

    if (pGroup.x() > 40 && pGroup.y() < 40) {
        towerToLeft();
    } else if (pGroup.x() < -40 && pGroup.y() < 40) {
        towerToRight();
    } else if (pGroup.x() < -25 && pGroup.y() > 55) {
        this->gun->turnToLeft();
    } else if (pGroup.x() > 25 && pGroup.y() > 55) {
        this->gun->turnToRight();
    } else if (pGroup.x() > -25 && pGroup.x() < 25 && pGroup.y() > 55) {
        if (shotFlag) {
            //如果没有了子弹或者生命值为0
            if (currentTower->getNumBom() <= 0 ||
                    currentTower->getLife() <= 0) {

            } else {
                gun->fire();
                currentTower->setNumBom(currentTower->getNumBom() - 1);
                currentTower->changNum();
                shotFlag = 0;
                readyShot();
            }
        }
    }

}

void TowerGroup::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        this->gun->turnToLeft();
        break;

    case Qt::Key_Right:
        this->gun->turnToRight();
        break;

    case Qt::Key_Space:
        if (shotFlag) {
            //如果没有了子弹或者生命值为0
            if (currentTower->getNumBom() <= 0 ||
                    currentTower->getLife() <= 0) {
                break;
            } else {
                gun->fire();
                currentTower->setNumBom(currentTower->getNumBom() - 1);
                shotFlag = 0;
                readyShot();
            }

        }

        break;

    default:
        break;
    }

}

//装弹函数
void TowerGroup::readyShot()
{
    Bomb * shotBomb;

    if (strList.value(1) == "triangleTower") {
        shotBomb = new TriangleBomb(QPointF(0,0));
    } else if (strList.value(1) == "squareTower") {
        shotBomb = new SquareBomb(QPointF(0,0));
    } else if (strList.value(1) == "circleTower") {
        shotBomb = new CircleBomb(QPointF(0,0));
    } else {
        ;
    }

    emit towerChanged(shotBomb, shotBomb->getShotSpeed(),
                      strList.value(1));
}

void TowerGroup::zhuangdanwanbi()
{
    shotFlag = 1;
}

void TowerGroup::towerWasAttacked()
{
    if (isColling()) {
        ;
    }

}

void TowerGroup::towerToLeft()
{
    QPropertyAnimation * animationCircle = new QPropertyAnimation(circleTower, "pos");
    QPropertyAnimation * animationTriangle = new QPropertyAnimation(triangleTower, "pos");
    QPropertyAnimation * animationSquare = new QPropertyAnimation(squareTower, "pos");

    //插入项目，0代表三角，1代表方块，2代表圆圈
    animationList << animationTriangle << animationSquare << animationCircle;

    for (int i = 0; i < 3; i++) {
        animationList.at(i)->setDuration(speed);
        animationList.at(i)->setStartValue(towerList.at(i)->pos());
    }

    animationList.at(1)->setEndValue(QPointF(-185, 0));
    animationList.at(2)->setEndValue(QPointF(0, 0));
    animationList.at(0)->setEndValue(QPointF(185, 0));

    animationList.at(0)->start();
    animationList.at(1)->start();
    animationList.at(2)->start();

    towerList.swap(0, 2);
    towerList.swap(0, 1);

    animationList.swap(0, 2);
    animationList.swap(0, 1);

    strList.swap(0, 2);
    strList.swap(0, 1);

    currentTower = towerList.at(1);

    readyShot();

    /***********************网络方面**************************/
    QByteArray datagram;

    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&datagram, QIODevice::WriteOnly);
    //代表炮塔改变，什么类型的炮塔, 向左还还是向右
    out << changeTower << strList.value(1) << tr("left");
    groupTowerSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 8888);

}

void TowerGroup::towerToRight()
{
    QPropertyAnimation * animationCircle = new QPropertyAnimation(circleTower, "pos");
    QPropertyAnimation * animationTriangle = new QPropertyAnimation(triangleTower, "pos");
    QPropertyAnimation * animationSquare = new QPropertyAnimation(squareTower, "pos");

    //插入项目，0代表三角，1代表方块，2代表圆圈
    animationList << animationTriangle << animationSquare << animationCircle;

    for (int i = 0; i < 3; i++) {
        animationList.at(i)->setDuration(speed);
        animationList.at(i)->setStartValue(towerList.at(i)->pos());
    }

    animationList.at(1)->setEndValue(QPointF(185, 0));
    animationList.at(2)->setEndValue(QPointF(-185, 0));
    animationList.at(0)->setEndValue(QPointF(0, 0));

    animationList.at(0)->start();
    animationList.at(1)->start();
    animationList.at(2)->start();

    towerList.swap(0, 2);
    towerList.swap(2, 1);

    animationList.swap(0, 2);
    animationList.swap(2, 1);

    strList.swap(0, 2);
    strList.swap(2, 1);

    currentTower = towerList.at(1);

    readyShot();

    /***********************网络方面**************************/
    QByteArray datagram;

    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&datagram, QIODevice::WriteOnly);
    //代表炮塔改变，什么类型的炮塔, 向左还还是向右
    out << changeTower << strList.value(1) << tr("right");
    groupTowerSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 8888);
}

