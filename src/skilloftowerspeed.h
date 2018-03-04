#ifndef SKILLOFTOWERSPEED_H
#define SKILLOFTOWERSPEED_H

#include "skill.h"
#include <QGraphicsObject>

class SkillOfTowerSpeed : public Skill
{
    Q_OBJECT
public:
    SkillOfTowerSpeed();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    void eatEffect();

};

#endif // SKILLOFTOWERSPEED_H
