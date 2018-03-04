#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QtNetwork>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QColor>
#include <QSound>
#include <QTime>

#include "explode.h"
#include "skillofaddbomb.h"
#include "skillofbox.h"
#include "skillofgunspeed.h"
#include "skilloftowerspeed.h"
#include "skillofwall.h"
#include "skillofreverse.h"

class Bomb : public QGraphicsObject
{
    Q_OBJECT

public:
    Bomb();

    //检测炸弹是否于物体发生了碰撞
    bool isColliding();

    //设置图形项的外框，炮弹都是21X21的
    QRectF boundingRect() const;

    //炮弹飞行函数,纯虚函数
    void fly();

    /*****************设置终点坐标******************/
    QPointF getDstPos() const;
    void setDstPos(const QPointF &value);

    //是否爆炸
    int getHasBombed() const;
    void setHasBombed(int value);

    /****************基本属性设置*******************/
    //设置位置，也就是通过目标位置获得发射方向
    void setPoint(const QPointF &value);
    //生命值
    int getLife() const;
    void setLife(int value);
    //设置威力大小
    void setPower(int value);
    int getPower() const;
    //判断时候在枪管中
    int getIsInGun() const;
    void setIsInGun(int value);

    int getShotSpeed() const;
    void setShotSpeed(int value);

    int getFlySpeed() const;
    void setFlySpeed(int value);

    //爆炸的虚汗数
    virtual void bombEffect() = 0;

signals:
    void wasCollided();

public slots:
    //炮弹碰撞处理函数
    virtual void dealColliding() = 0;

private:
    //要移动的方向坐标
    //用于确定移动的方向
    //x, y用来确定要移动的方向
    QPointF point;
    int x, y;

    /*一些基本属性*/
    //射程
    int instance;
    //破坏力大小
    int power;
    //炸弹的飞行速度
    int flySpeed;
    //炸弹的装弹速度
    int shotSpeed;
    //威力范围
    QPainterPath area;
    //生命值
    int life;

    QTimer * timer;

    //发送网络广播
    //暂时不使用服务器方式，只使用广播方式
    QUdpSocket * bombSender;

    QPointF dstPos;

    //判断时候已经爆炸
    int hasBombed;
    //判断数否在枪管中
    int isInGun;
};

#endif // BOMB_H
