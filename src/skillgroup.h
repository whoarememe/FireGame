#ifndef SKILLGROUP_H
#define SKILLGROUP_H

#include "firebutton.h"
#include "gunturntoleft.h"
#include "gunturntoright.h"
#include "skillofaddbomb.h"
#include "skillofgunspeed.h"
#include "skilloftowerspeed.h"
#include "skillofwall.h"
#include "skillofbox.h"

#include "QObject"
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTime>

#define SKILL_TIME_RAND 1000

class SkillGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    SkillGroup();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void generateSkill();

private:
    SkillOfGunSpeed * skillOfGunSpeed;
    SkillOfTowerSpeed * skillOfTowerSpeed;
    SkillOfaddBomb * skillOfaddBomb;
    SkillOfWall * skillOfWall;

    QTimer * timer;

    QList<QString> strSkill;
};

#endif // SKILLGROUP_H
