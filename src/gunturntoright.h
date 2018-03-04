#ifndef GUNTURNTORIGHT_H
#define GUNTURNTORIGHT_H

#include <QGraphicsObject>

class GunTurnToRight : public QGraphicsObject
{
    Q_OBJECT
public:
    GunTurnToRight();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);
};

#endif // GUNTURNTORIGHT_H
