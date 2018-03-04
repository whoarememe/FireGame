#ifndef MYVIEW_H
#define MYVIEW_H

#include "tower.h"
#include "gun.h"

#include <QGraphicsView>

#define SCREEN_WIDTH    540
#define SCREEN_HEIGTH   810

#define VIEW_WIDTH      540
#define VIEW_HEIGHT     810

#define SCENE_WIDTH     530
#define SCENE_HEIGHT    800

class MyView : public QGraphicsView
{
public:
    MyView();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    //更改外观
    void changeTowerAppear();

private:
    //初始化视图
    void initView();

    //战场边界
    QGraphicsLineItem * topLine;
    QGraphicsLineItem * bottomLine;
    QGraphicsLineItem * leftLine;
    QGraphicsLineItem * rightLine;

    //我方炮塔
    Tower * ourTriangleTower;
    Tower * ourSquareTower;
    Tower * ourCircleTower;

    //敌人炮塔
    Tower * enemyTriangleTower;
    Tower * enemySquareTower;
    Tower * enemyCircleTower;

    //我方炮管
    Gun * ourGun;
    //敌方paogaun
    Gun * enemyGun;
};

#endif // MYVIEW_H
