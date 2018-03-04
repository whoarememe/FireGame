#ifndef SKILLOFWALL_H
#define SKILLOFWALL_H

#include "skill.h"

class SkillOfWall : public Skill
{
    Q_OBJECT
public:
    SkillOfWall();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    void eatEffect();
};

#endif // SKILLOFWALL_H
