#ifndef SKILLOFADDBOMB_H
#define SKILLOFADDBOMB_H

#include "skill.h"
#include <QGraphicsObject>

class SkillOfaddBomb : public Skill
{
    Q_OBJECT
public:
    SkillOfaddBomb();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
    void eatEffect();

};

#endif // SKILLOFADDBOMB_H
