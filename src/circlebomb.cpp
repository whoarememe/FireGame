#include "circlebomb.h"
#include "gun.h"
#include "tower.h"
#include "skill.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include <typeinfo>

CircleBomb::CircleBomb(QPointF point)
{
    //威力最大
    setPower(40);
    //装弹最慢
    setShotSpeed(2000);
    //速度最慢
    setFlySpeed(8000);
    //设置生命值
    setLife(40);
}

void CircleBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    //设置画笔颜色
    //绘制一个圆形炸弹
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawEllipse(-5, -5, 10, 10);

    //如果是在枪管中，不触发任何碰撞
    if (getIsInGun()) {

    } else {
        if (isColliding()) {
            emit wasCollided();
//            setHasBombed(1);
        }
    }

}

QPainterPath CircleBomb::shape() const
{
    //碰撞检测边缘跟炸弹一样大
    QPainterPath path;
    path.addEllipse(-2, -2, 4, 4);

    return path;
}

void CircleBomb::bombEffect()
{
    //爆炸的效果和声音
    explode * pic = new explode(3);
    scene()->addItem(pic);
    pic->setPos(this->pos());
    QSound::play(":/sound/sound/bomb.wav");

    //删除爆炸物
    deleteLater();
}

void CircleBomb::dealColliding()
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
            qDebug() << "圆形遇到了bomb";
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


