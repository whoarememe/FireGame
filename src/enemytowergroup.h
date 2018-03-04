#ifndef ENEMYTOWERGROUP_H
#define ENEMYTOWERGROUP_H

#include "circletower.h"
#include "triangletower.h"
#include "squaretower.h"
#include "gun.h"
#include "circlebomb.h"
#include "trianglebomb.h"
#include "squarebomb.h"

#include <QPropertyAnimation>
#include <QGraphicsItemGroup>
#include <QMap>
#include <QtNetwork>
#include <QGraphicsObject>

class enemyTowerGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    enemyTowerGroup();


//    bool isColling();

//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);

signals:
    //塔改变信号
    void towerChanged(Bomb * bomb, int speed, QString str);

private slots:
    //信号处理函数
    void signalDeal();
//    //准备就绪，发射
//    void readyShot();
//    void zhuangdanwanbi();

private:
    QUdpSocket * groupReciveSocket;
    //装弹完毕为1
    int shotFlag;

    Tower * circleTower;
    Tower * triangleTower;
    Tower * squareTower;

    Gun * gun;

    Bomb * shotBomb;
    CircleBomb * circleBomb;
    TriangleBomb * triangleBomb;
    SquareBomb * squareBomb;

    QString currentTowerStr;

    /*************有关炮塔和炮管的属性*****************/
    void towerToLeft();
    void towerToRight();
    void gunToLeft();
    void gunToRight();
    QTransform gunTransform;
    int rotationItem;

    /**************有关炮弹的包括初始坐标，目标坐标速度等************************/
    int flyBombSpeed;
    QPointF flyBombSrc;
    QPointF flyBombDst;
    void fire();    //发射函数
    QString bombStr;

//    //当前炮台
//    Tower * currentTower;
//    int currentId;

//    //切换速度
//    int speed;

    //用于切换
    QList<QPropertyAnimation *> animationList;
    QList<Tower *> towerList;
//    QList<QString> strList;
//    QMap<Tower *, Bomb *> mapTowerBomb;
//    QMap<Bomb *, int > mapBombSpeed;

//    //塔被攻击
//    void towerWasAttacked();

//    QUdpSocket * groupTowerSocket;

    //相关函数
    void ready();
};

#endif // ENEMYTOWERGROUP_H
