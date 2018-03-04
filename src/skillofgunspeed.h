#ifndef SKILLOFGUNSPEED_H
#define SKILLOFGUNSPEED_H

#include "skill.h"
#include <QGraphicsObject>

class SkillOfGunSpeed : public Skill
{
    Q_OBJECT
public:
    SkillOfGunSpeed();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    void eatEffect();

};

#endif // SKILLOFGUNSPEED_H
