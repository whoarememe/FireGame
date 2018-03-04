#include "enemytowergroup.h"

enemyTowerGroup::enemyTowerGroup():
    rotationItem(0), shotFlag(0)
{
    //这个只是演示的动画组，所以可以不用设置焦点

    //初始化值
    //炮塔
    circleTower = new CircleTower;
    triangleTower = new TriangleTower;
    squareTower = new SquareTower;

    /*********************炮塔属性设置********************/
    circleTower->setLife(300);
    squareTower->setLife(200);
    triangleTower->setLife(100);

    //炸弹
    circleBomb = new CircleBomb(QPointF(0, 0));
    squareBomb = new SquareBomb(QPointF(0, 0));
    triangleBomb = new TriangleBomb(QPointF(0, 0));
    shotBomb = new SquareBomb(QPointF(0, 0));

    gun = new Gun(squareBomb, 1000);

    currentTowerStr = "squareTower";

    //添加到组
    addToGroup(circleTower);
    addToGroup(triangleTower);
    addToGroup(squareTower);
    addToGroup(gun);

    //设置坐标
    triangleTower->setPos(-185, 0);
    squareTower->setPos(0, 0);
    circleTower->setPos(185, 0);
    gun->setPos(0, -20);

    towerList << triangleTower << squareTower << circleTower;

    gunTransform = gun->transform();

    /*******************初始化udp************************/
    groupReciveSocket = new QUdpSocket(this);
    groupReciveSocket->bind(8999, QUdpSocket::ShareAddress);
    connect(groupReciveSocket, SIGNAL(readyRead()), this, SLOT(signalDeal()));

    //炮塔改变
    connect(this, SIGNAL(towerChanged(Bomb*, int, QString)),
            gun, SLOT(towerChanged(Bomb*, int, QString)));

    qDebug() << "connect NET";
}

/**************************************信息处理**************************************/
void enemyTowerGroup::signalDeal()
{
    //首先获得第一个标志位，看看这个事干什么的
    //当拥有等待的数据的时候
    while (groupReciveSocket->hasPendingDatagrams()) {
        QByteArray datagram;

        //pendingDatagramSize为返回第一个在等待读取报文的size，
        //resize函数是把datagram的size归一化到参数size的大小一样
        datagram.resize(groupReciveSocket->pendingDatagramSize());
        //然后读取数据
        groupReciveSocket->readDatagram(datagram.data(), datagram.size());
        //数据流输入
        QDataStream inStream(&datagram, QIODevice::ReadOnly);

        //数据类型，看看是炮塔旋转还是怎么地
        int type;

        inStream >> type;

        switch (type) {
        case changeTower: {
            qDebug() << "change Tower";
            QString str;

            inStream >> currentTowerStr;
            inStream >> str;

            if (str == "left") {
                towerToLeft();
            } else if (str == "right") {
                towerToRight();
            }

            ready();

            break;
        }
        case rotateGun:{
            qDebug() << "rotateGun";
            QString str;

            inStream >> str;
            inStream >> rotationItem;
            if ( str == "left" ) {
                qDebug() << "i will turn to ";
                gunToLeft();
            } else if ( str == "right" ) {
                gunToRight();
            } else {
                ;
            }
            break;
        }
        case fireBomb: {
            inStream >> bombStr >> flyBombSrc >> flyBombDst >> flyBombSpeed;
            this->fire();
            qDebug() << "fireBomb";
            break;
        }
        case setAttr:
            qDebug() << "setAttr";
            break;
        case gameOver:
            qDebug() << "gameOver";
            break;
        default:
            break;
        }
    }
}

/*******************************炮塔切换***********************************/
void enemyTowerGroup::towerToLeft()
{
    QPropertyAnimation * animationCircle = new QPropertyAnimation(circleTower, "pos");
    QPropertyAnimation * animationTriangle = new QPropertyAnimation(triangleTower, "pos");
    QPropertyAnimation * animationSquare = new QPropertyAnimation(squareTower, "pos");

    //插入项目，0代表三角，1代表方块，2代表圆圈
    animationList << animationTriangle << animationSquare << animationCircle;

    for (int i = 0; i < 3; i++) {
        animationList.at(i)->setDuration(1000);
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
}

void enemyTowerGroup::towerToRight()
{
    QPropertyAnimation * animationCircle = new QPropertyAnimation(circleTower, "pos");
    QPropertyAnimation * animationTriangle = new QPropertyAnimation(triangleTower, "pos");
    QPropertyAnimation * animationSquare = new QPropertyAnimation(squareTower, "pos");

    //插入项目，0代表三角，1代表方块，2代表圆圈
    animationList << animationTriangle << animationSquare << animationCircle;

    for (int i = 0; i < 3; i++) {
        //这里本应高由速度
        animationList.at(i)->setDuration(1000);
        animationList.at(i)->setStartValue(towerList.at(i)->pos());
    }

    animationList.at(1)->setEndValue(QPointF(185, 0));
    animationList.at(2)->setEndValue(QPointF(-185, 0));
    animationList.at(0)->setEndValue(QPointF(0, 0));

    animationList.at(0)->start();
    animationList.at(1)->start();
    animationList.at(2)->start();

    towerList.swap(0, 2);
    towerList.swap(0, 1);

    animationList.swap(0, 2);
    animationList.swap(2, 1);
}

/********************************炮塔的旋转****************************************/
void enemyTowerGroup::gunToLeft()
{
    gunTransform.rotate(-1);
    rotationItem -= 1;
    if (rotationItem < -70 || rotationItem > 70) {
        gunTransform.rotate(1);
        rotationItem += 1;
    }

    gun->setTransform(gunTransform);
}

void enemyTowerGroup::gunToRight()
{
    gunTransform.rotate(1);
    rotationItem += 1;
    if (rotationItem < -70 || rotationItem > 70) {
        gunTransform.rotate(-1);
        rotationItem -= 1;
    }

    gun->setTransform(gunTransform);
}

/*********************************开火模拟**********************************************/
void enemyTowerGroup::fire()
{
    Bomb * flyBomb;
    ready();

    QPointF beginPoint;
    QPointF endPoint;

    beginPoint.setX(265 - (flyBombSrc.x() - 265));
    beginPoint.setY(400 - (flyBombSrc.y() - 400));
    endPoint.setX(265 - (flyBombDst.x() - 265));
    endPoint.setY(400 - (flyBombDst.y() - 400));

    qDebug() << "原来的开始" << flyBombSrc << "原终点" << flyBombDst;
    qDebug() << "开始地点" << beginPoint << "结束" << endPoint;

    if (currentTowerStr == "triangleTower") {
        flyBomb = new TriangleBomb(QPointF(0,0));
    } else if (currentTowerStr == "squareTower") {
        flyBomb = new SquareBomb(QPointF(0,0));
    } else if (currentTowerStr == "circleTower") {
        flyBomb = new CircleBomb(QPointF(0,0));
    } else {
        ;
    }

    scene()->addItem(flyBomb);
    flyBomb->setRotation(180);
    flyBomb->setPos(beginPoint);
    flyBomb->setDstPos(endPoint);

//    QSound::play(":/sound/sound/fireSound.wav");
    flyBomb->fly();
}

/*********************************装弹模拟**********************************************/
void enemyTowerGroup::ready()
{
    Bomb * shotBomb;

    //装弹函数
    if (currentTowerStr == "triangleTower") {
        shotBomb = new TriangleBomb(QPointF(0,0));
    } else if (currentTowerStr == "squareTower") {
        shotBomb = new SquareBomb(QPointF(0,0));
    } else if (currentTowerStr == "circleTower") {
        shotBomb = new CircleBomb(QPointF(0,0));
    } else {
        ;
    }

    emit towerChanged(shotBomb, shotBomb->getShotSpeed(), currentTowerStr);
}
