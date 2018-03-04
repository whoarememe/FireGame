#include "skillofreverse.h"

#include <QPainter>

SkillOfReverse::SkillOfReverse()
{

}

/*****************************************基本绘制****************************************/
void SkillOfReverse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/skill/pic/texiaozu/reverse.png");

    painter->drawPixmap(-pixmap.width()/2, -pixmap.height()/2, pixmap);
}

void SkillOfReverse::eatEffect()
{
    explode * pic = new explode(4);
    scene()->addItem(pic);
    pic->setPos(this->pos());
    QSound::play(":/sound/sound/eatKill.wav");

    this->getTimer()->start();
    this->deleteLater();
}
