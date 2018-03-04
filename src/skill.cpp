#include "skill.h"

#include <QDebug>

Skill::Skill(): numb(0)
{
}

QRectF Skill::boundingRect() const
{
    qreal penwidth = 1;

    return QRectF(-25 - penwidth/2, -25 - penwidth/2,
                  50 + penwidth, 50 + penwidth);

}

QPainterPath Skill::shape()
{
    QPainterPath path;
    path.addRect(-20, -20, 40, 40);

    return path;
}

bool Skill::isColliding()
{
    if (this->collidingItems().count() > 1) {
        return true;
    } else {
        return false;
    }

}

QTimer *Skill::getTimer() const
{
    return timer;
}

void Skill::setTimer(QTimer *value, int existTime)
{
    value->stop();
    timer = value;

    timerSelf = new QTimer(this);
    connect(timerSelf, SIGNAL(timeout()), this, SLOT(deleteSelf()));
    timerSelf->start(existTime);
}

void Skill::deleteSelf()
{
    timer->start();
    deleteLater();
}

int Skill::getNumb() const
{
    return numb;
}

void Skill::setNumb(int value)
{
    numb = value;
}

