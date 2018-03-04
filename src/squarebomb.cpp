#include "squarebomb.h"
#include "gun.h"
#include "tower.h"
#include "skill.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <typeinfo>
#include <QDebug>

SquareBomb::SquareBomb(QPointF point)
{
    //威力中等.shengmingjishiweili
    setPower(20);
    //装弹最慢
    setShotSpeed(700);
    //速度一般般
    setFlySpeed(6000);
    //设置生命值
    setLife(20);
}

/*****************************************炮弹的绘制***************************************/
void SquareBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    painter->drawRect(-5, -5, 10, 10);

    //如果是在枪管中，不触发任何碰撞
    if (getIsInGun()) {

    } else {
        if (isColliding() ) {
            emit wasCollided();
//            setHasBombed(1);
        }
    }
}

QPainterPath SquareBomb::shape() const
{
    //碰撞检测边缘跟炸弹一样大
    QPainterPath path;
    path.addRect(-5, -5, 10, 10);

    return path;
}

void SquareBomb::bombEffect()
{
    /*******************爆炸效果************************/
    //爆炸的效果和声音
    explode * pic = new explode(1);
    scene()->addItem(pic);
    pic->setPos(this->pos());
    QSound::play(":/sound/sound/bomb.wav");

    //删除爆炸物
    deleteLater();
}

void SquareBomb::dealColliding()
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

            } else if (this->getPower() == dynamic_cast<Bomb *> (item)->getPower()) {
                qDebug() << "方块执行了xiaohui函数";
                this->bombEffect();
            }
            qDebug() << "方块遇到了bomb";
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
