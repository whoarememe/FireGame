#include "skillgroup.h"

#include <QList>
#include <QGraphicsScene>
#include <QDebug>

SkillGroup::SkillGroup()
{
    setFlag(QGraphicsObject::ItemIsFocusable);
//    setFlag(QGraphicsObject::ItemIsMovable);

    timer = new QTimer(this);

    //随机数种子
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    skillOfGunSpeed = new SkillOfGunSpeed();
    skillOfTowerSpeed = new SkillOfTowerSpeed();
    skillOfaddBomb = new SkillOfaddBomb();
    skillOfWall = new SkillOfWall();

    addToGroup(skillOfGunSpeed);
    addToGroup(skillOfTowerSpeed);
    addToGroup(skillOfaddBomb);
    addToGroup(skillOfWall);


    skillOfGunSpeed->setPos(-210, 0);
    skillOfTowerSpeed->setPos(-160, 0);
    skillOfaddBomb->setPos(210, 0);
    skillOfWall->setPos(160, 0);

    //装入技能池
    strSkill << "skillOfGunSpeed" << "skillOfTowerSpeed" << "skillOfaddBomb"
             << "skillOfWall" << "skillOfBox" << "skillOfRe";


    connect(timer, SIGNAL(timeout()), this, SLOT(generateSkill()));

    timer->start(SKILL_TIME_RAND);
}

void SkillGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItemGroup::mousePressEvent(event);

}

void SkillGroup::generateSkill()
{
    Skill * skill;

    int skillNum = qrand()%6;

    switch (skillNum) {
    case 0:
        skill = new SkillOfGunSpeed();
        break;
    case 1:
        skill = new SkillOfTowerSpeed();
        break;
    case 2:
        skill = new SkillOfaddBomb();
        break;
    case 3:
        skill = new SkillOfWall();
        break;
    case 4:
        skill = new SkillOfBox();
        break;
    case 5:
        skill = new SkillOfGunSpeed();
        break;
    default:
        skill = new SkillOfGunSpeed();
        break;
    }

    skill->setTimer(this->timer, qrand()%1000+3000);

    int x = qrand()%470 + 30;
    int y = qrand()%350+ 250;

    scene()->addItem(skill);
    skill->setPos(x, y);
}
