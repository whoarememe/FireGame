#ifndef TOWERGROUP_H
#define TOWERGROUP_H

#include "circletower.h"
#include "triangletower.h"
#include "squaretower.h"
#include "gun.h"
#include "circlebomb.h"
#include "trianglebomb.h"
#include "squarebomb.h"

#include "firebutton.h"
#include "gunturntoleft.h"
#include "gunturntoright.h"

#include <QPropertyAnimation>
#include <QGraphicsItemGroup>
#include <QMap>
#include <QtNetwork>

class TowerGroup: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    TowerGroup();

    bool isColling();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    //塔改变信号
    void towerChanged(Bomb * bomb, int speed, QString str);

private slots:
    //准备就绪，发射
    void readyShot();
    void zhuangdanwanbi();

private:
    //装弹完毕为1
    int shotFlag;

    Tower * circleTower;
    Tower * triangleTower;
    Tower * squareTower;

    Gun * gun;

    CircleBomb * circleBomb;
    TriangleBomb * triangleBomb;
    SquareBomb * squareBomb;

    //当前炮台
    Tower * currentTower;
    int currentId;

    //切换速度
    int speed;

    //用于切换
    QList<QPropertyAnimation *> animationList;
    QList<Tower *> towerList;
    QList<QString> strList;
    QMap<Tower *, Bomb *> mapTowerBomb;
//    QMap<Bomb *, int > mapBombSpeed;

    //塔被攻击
    void towerWasAttacked();

    //切换塔
    void towerToLeft();
    void towerToRight();

    QUdpSocket * groupTowerSocket;

    /************技能组属性****************/
    FireButton * fireButton;
    GunTurnToLeft * gunTurnToLeft;
    GunTurnToRight * gunTurnToRight;
};

#endif // TOWERGROUP_H
