#ifndef GUN_H
#define GUN_H

#include <QGraphicsObject>
#include <QMouseEvent>
#include <QtNetwork>

#include "bomb.h"


//我们在这里定义一下
//1代表炮塔切换
//2代表炮管旋转
//3代表炮弹发射
//4定义一些属性，保留
//使用端口8888进行广播
enum MessageType{changeTower, rotateGun, fireBomb, setAttr, Refuse, gameOver};

class Gun : public QGraphicsObject
{
    Q_OBJECT

public:
    Gun();
    Gun(Bomb * bomb, int speed);

    //准备函数
    void ready(Bomb * bomb, QString str);

    //炮塔旋转
    void turnToLeft();
    void turnToRight();

    //开火函数
    void fire();

    //炮管大小15X40
    QRectF boundingRect() const;

    //绘制炮管
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    QPainterPath shape() const;

    QTransform getOldTransform() const;
    void setOldTransform(const QTransform &value);

    int getLife() const;
    void setLife(int value);

protected:


signals:
    //装弹完毕
    void finishShot();

    //已经发射
    void hasShot();

private slots:
    //发射装弹完毕信号
    void emitFinishShot();

    //炮塔更改，重新装弹
    void towerChanged(Bomb * bomb, int speed, QString str);

private:
    //要装填耳朵弹药
    Bomb * bomb;
    //发射之后的弹药
    Bomb * flyBomb;
    //装弹速度
    int speed;
    //变换矩阵
    QTransform oldTransform;
    //保存旋转角度
    int rotationItem;
    //发送一些信息
    QUdpSocket * gunSender;
    QString str;

    //生命值,炮塔的生命值无限大设置为1
    int life;
    //威力,无限大-1
    int power;

};

#endif // GUN_H
