#include "skillofwall.h"

SkillOfWall::SkillOfWall()
{

}

void SkillOfWall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/skill/pic/texiaozu/wall.png");

    painter->drawPixmap(-pixmap.width()/2, -pixmap.height()/2, pixmap);
}

void SkillOfWall::eatEffect()
{
    explode * pic = new explode(4);
    scene()->addItem(pic);
    pic->setPos(this->pos());
    QSound::play(":/sound/sound/eatKill.wav");

    this->getTimer()->start();
    this->deleteLater();
}
