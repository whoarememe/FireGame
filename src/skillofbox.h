#ifndef SKILLOFBOX_H
#define SKILLOFBOX_H

#include "skill.h"

class SkillOfBox : public Skill
{
    Q_OBJECT

public:
    SkillOfBox();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    void eatEffect();

};

#endif // SKILLOFBOX_H
