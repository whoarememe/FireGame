#ifndef SKILLOFREVERSE_H
#define SKILLOFREVERSE_H

#include "skill.h"

class SkillOfReverse : public Skill
{
public:
    SkillOfReverse();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    void eatEffect();

};

#endif // SKILLOFREVERSE_H
