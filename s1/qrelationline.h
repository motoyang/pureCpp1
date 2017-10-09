#ifndef QRELATIONLINE_H
#define QRELATIONLINE_H

#include <qgraphicsitem.h>

class QRelationLine : public QGraphicsItem
{
    enum LineType {
        Straight,
        polygonal,
        broken,
        Cubic,
        Perpendicular
    };

    QPointF m_p1, m_p2;

    QPainterPath arrowPath(const QLineF& l) const;
    QPainterPath trianglePath(const QLineF& l) const;
    QPainterPath diamondPath(const QLineF& l) const;
    QPainterPath path() const;

public:
    QRelationLine(QGraphicsItem *parent = Q_NULLPTR);
    void setLine(const QPointF& p1, const QPointF& p2);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


};

class QBrokenLine : public QGraphicsItem
{
    QVector<QPointF> m_points;
    int m_fromAngle, m_toAngle;
    QPointF m_fromPoint, m_toPoint;

    void route();
    QPainterPath path() const;

public:
    QBrokenLine(QGraphicsItem *parent = Q_NULLPTR);
    void setAnglePoints(int fromA, const QPointF& fromP, int toA, const QPointF& toP);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


};

#endif // QRELATIONLINE_H
