#include "trianglebomb.h"
#include "gun.h"
#include "tower.h"
#include "skill.h"

#include <QPainter>
#include <QPropertyAnimation>
TriangleBomb::TriangleBomb(QPointF point)
{
    //威力最小
    setPower(10);
    //装弹最慢
    setShotSpeed(400);
    //速度一般般
    setFlySpeed(4000);
    //设置生命值
    setLife(10);
}

void TriangleBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    //设置画笔颜色
    //绘制一个圆形炸弹
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    //使用多边形绘制路径
    QPolygonF polygon;
    polygon << QPointF(-5, 5) << QPointF(0, -5)
            << QPointF(5, 5)  << QPointF(-5, 5);

    //绘制一个三角形
    painter->drawPolygon(polygon);

    //如果是在枪管中，不触发任何碰撞
    if (getIsInGun()) {

    } else {
        if (isColliding()) {
            emit wasCollided();
//            setHasBombed(1);
        }
    }

}

QPainterPath TriangleBomb::shape() const
{
    //使用多边形绘制路径
    QPolygonF polygon;
    polygon << QPointF(-5, 5) << QPointF(0, -5)
            << QPointF(5, 5)  << QPointF(-5, 5);

    //绘制了多变型--三角形
    //不知道使用lineTo可不可以，待会试一下
    QPainterPath path;
    path.addPolygon(polygon);

    return path;

}

//执行这个函数就会爆炸并且结束了
void TriangleBomb::bombEffect()
{
    //爆炸的效果和声音
    explode * pic = new explode(2);
    scene()->addItem(pic);
    pic->setPos(this->pos());
    QSound::play(":/sound/sound/bomb.wav");


    //删除爆炸物
    deleteLater();
}

void TriangleBomb::dealColliding()
{
    /********************碰撞事物检测********************/
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    foreach (QGraphicsItem * item, collidingItems) {
        //进行类型检查与转换
        if (dynamic_cast<Bomb *> (item) != NULL) {
            //如果自己的威力小于对手的生命值，那么自己销毁，同时对手的生命值和威力改变
            if (this->getPower() < dynamic_cast<Bomb *> (item)->getPower()) {
                //如果对手已经爆炸，那就不用管了
                if (dynamic_cast<Bomb *> (item)->getHasBombed()) ;
                else {
                    this->setHasBombed(1);
                    //威力减半
                    qDebug() << "方块执行了威力减半函数";
                    dynamic_cast<Bomb *> (item)->setPower(dynamic_cast<Bomb *> (item)->getPower() -
                                                          this->getPower());

                    this->bombEffect();
                }
            qDebug() << "三角遇到了bomb";
            }
        } else if (dynamic_cast<Tower *> (item) != NULL) {
            dynamic_cast<Tower *> (item)->setLife(dynamic_cast<Tower *> (item)->getLife()
                                                  - this->getPower());
            dynamic_cast<Tower *> (item)->changeAppear(QColor(213, 0, 0));
            dynamic_cast<Tower *> (item)->towerWasAttackSound();
            this->bombEffect();
        } else if (dynamic_cast<Skill *> (item) != NULL) {
            qDebug() << "遇到了skill";
            dynamic_cast<Skill *> (item)->eatEffect();
            if (dynamic_cast<SkillOfaddBomb *> (item) != NULL) {
                qDebug() << "这个是加子弹技能";
            } else if (dynamic_cast<SkillOfBox *> (item) != NULL) {
                qDebug() << "这个是盒子技能";
            } else if (dynamic_cast<SkillOfGunSpeed *> (item) != NULL) {
                qDebug() << "这个是加速技能";
            } else if (dynamic_cast<SkillOfTowerSpeed *> (item) != NULL) {
                qDebug() << "这个是切换加速技能";
            } else if (dynamic_cast<SkillOfWall *> (item) != NULL) {
                qDebug() << "这是技能墙";
            } else if (dynamic_cast<SkillOfReverse *> (item) != NULL) {
                qDebug() << "这是眩晕技能";
            }
            this->deleteLater();
        }

    }

}
