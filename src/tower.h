#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QSound>

class Tower : public QGraphicsObject
{
    Q_OBJECT

public:
    Tower();

    //50X50范围
    QRectF boundingRect() const;

    //炮塔颜色
    QColor getTowerColor() const;
    void setTowerColor(const QColor &value);

    int getNumBom() const;
    void setNumBom(int value);

    int getLife() const;
    void setLife(int value);

    bool isColliding();

    QPainter *getPainter() const;
    void setPainter(QPainter *value);

    void changNum();

    void changeAppear(QColor color);

    void towerWasAttackSound();

signals:
    void wasAttacked();
    void numChanged();

private slots:
    void isSolliding();
    void resumeAppear();

private:
    //炮塔颜色
    QColor towerColor;

    /**************炮塔的基本属性****************/
    //炮塔的炮弹数量
    int numBom;
    //炮塔生命值
    int life;
    //炮塔威力,一般这个值设置的特别大，比任意一款炮弹的威力都要大
    int power;

    QPainter * painter;
    QGraphicsDropShadowEffect * dropEffect = new QGraphicsDropShadowEffect;
    QGraphicsColorizeEffect * colorEffect = new QGraphicsColorizeEffect;
    QPropertyAnimation * animation = new QPropertyAnimation;

    QPointF currentPos;
};


#endif // TOWER_H
