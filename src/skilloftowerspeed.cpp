#include "skilloftowerspeed.h"

#include <QPainter>
#include <QTimer>

SkillOfTowerSpeed::SkillOfTowerSpeed()
{

}

/*****************************************基本绘制****************************************/
void SkillOfTowerSpeed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/skill/pic/texiaozu/paotaiqihuan.png");

    painter->drawPixmap(-pixmap.width()/2, -pixmap.height()/2, pixmap);
}

void SkillOfTowerSpeed::eatEffect()
{
    explode * pic = new explode(4);
    scene()->addItem(pic);
    pic->setPos(this->pos());
    QSound::play(":/sound/sound/eatKill.wav");

    this->getTimer()->start();
    this->deleteLater();
}
