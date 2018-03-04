#include "myview.h"

#include "circletower.h"
#include "squaretower.h"
#include "triangletower.h"

#include "gun.h"

#include "circlebomb.h"
#include "trianglebomb.h"
#include "squarebomb.h"

#include "towergroup.h"
#include "enemytowergroup.h"

#include "skillgroup.h"

#include <QIcon>
#include <QPropertyAnimation>
#include <QGraphicsEffect>

MyView::MyView()
{
    initView();
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug("hello");
    QGraphicsView::mouseMoveEvent(event);
}

void MyView::keyPressEvent(QKeyEvent * event)
{
    QGraphicsView::keyPressEvent(event);
}

void MyView::initView()
{
    //抗锯齿
    setRenderHint(QPainter::Antialiasing);
    //设置缓存背景, 加快渲染速度
    setCacheMode(CacheBackground);
    //设置标题
    setWindowTitle(tr("图形之争"));
    //设置应用图标,就是状态栏里面的图标
    setWindowIcon(QIcon(":/pic/tubiao/ico.png"));
    //设置大小
    setMinimumSize(SCREEN_WIDTH, SCREEN_HEIGTH);
    setMaximumSize(SCREEN_WIDTH, SCREEN_HEIGTH);

    //然后设置战争场景
    QGraphicsScene * warScene = new QGraphicsScene;
    //设置场景矩形
    warScene->setSceneRect(5, 5, SCENE_WIDTH, SCENE_HEIGHT);

    warScene->setBackgroundBrush(QPixmap(":/pic/back/background.png"));

    setScene(warScene);

    //设置战场边界
    topLine = warScene->addLine(0, 50, VIEW_WIDTH, 50);
    rightLine = warScene->addLine(VIEW_WIDTH, 0, VIEW_WIDTH, SCENE_HEIGHT);
    leftLine = warScene->addLine(0, 0, 0, SCENE_HEIGHT);
    bottomLine = warScene->addLine(0, SCENE_HEIGHT-50, VIEW_WIDTH, SCENE_HEIGHT-50);

    TowerGroup * ourTowerGroup = new TowerGroup;
    warScene->addItem(ourTowerGroup);
    ourTowerGroup->setPos(265, 700);

    QTransform transfo;
    transfo.rotate(180);
    enemyTowerGroup * enemyTGroup = new enemyTowerGroup();
    warScene->addItem(enemyTGroup);
    enemyTGroup->setTransform(transfo);
    enemyTGroup->setPos(265, 100);

    SkillGroup * skillGroup = new SkillGroup();
    warScene->addItem(skillGroup);
    skillGroup->setPos(265, 775);


//    QKeyEvent myevent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
//    qApp->sendEvent(warScene, &myevent);
}
