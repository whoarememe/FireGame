#ifndef SKILL_H
#define SKILL_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>

#include "explode.h"

//存在3秒
#define TIMER_SLEF_EXIST 3000

class Skill : public QGraphicsObject
{
    Q_OBJECT

public:
    Skill();

    QRectF boundingRect() const;
    QPainterPath shape();

    bool isColliding();

    QTimer *getTimer() const;
    void setTimer(QTimer *value, int existTime);

    int getNumb() const;
    void setNumb(int value);

    virtual void eatEffect() = 0;

public slots:
    void deleteSelf();

private:
    //当被吃掉之后重新启动定时器
    QTimer * timer;

    //技能存在时间计时器
    QTimer * timerSelf;

    /*********基本属性***************/
    //存在时间
//    int existTime;
    //技能数量
    int numb;

};

#endif // SKILL_H
