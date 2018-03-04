#ifndef FIREBUTTON_H
#define FIREBUTTON_H

#include <QGraphicsObject>
#include <QMouseEvent>
#include <QPushButton>
#include <QObject>

class FireButton : public QGraphicsObject
{
    Q_OBJECT

public:
    FireButton();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option,
               QWidget * widget);

protected:
    void mousePressEvent(QMouseEvent * event);

private:

};

#endif // FIREBUTTON_H
