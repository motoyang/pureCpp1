//#include <qpainter.h>
//#include <qgraphicsitem.h>
//#include <qdebug.h>
//#include "precompiled.h"
#include "qrelationline.h"

// 在线段l的终点画箭头
QPainterPath QRelationLine::arrowPath(const QLineF &l) const
{
    const qreal ArrowAngle = 30.0;
    const qreal ArrowLength = 10.0;

    QPainterPath pp;
    QLineF l2(l.p2(), l.p1());
    QLineF l3(l2);

    // 找出三个点
    l3.setLength(ArrowLength);
    l3.setAngle(l2.angle() - ArrowAngle);
    QPointF p1 = l3.p2();
    l3.setAngle(l2.angle() + ArrowAngle);
    QPointF p2 = l3.p2();

    // 画箭头，注意pp终点的位置
    pp.moveTo(l3.p1());
    pp.lineTo(p2);
    pp.moveTo(p1);
    pp.lineTo(l3.p1());

    return pp;
}

// 在线段l的终点画三角形，pp的终点在三角形底边的中点
QPainterPath QRelationLine::trianglePath(const QLineF &l) const
{
    const qreal TriangleAngle = 30.0;
    const qreal TriangleLength = 8.0;

    QLineF l2(l.p2(), l.p1());
    QLineF l3(l2);
    l3.setLength(TriangleLength);

    // 找出三角形的三个顶点
    l3.setAngle(l2.angle() - TriangleAngle);
    QPointF p1 = l3.p2();
    QPointF p2 = l3.p1();
    l3.setAngle(l2.angle() + TriangleAngle);
    QPointF p3 = l3.p2();

    // 找出三角形底边的中点
    QPointF p4 = QLineF(p3, p1).center();

    // 从底边的中点开始画三角形
    QPainterPath pp;
    pp.moveTo(p4);
    pp.lineTo(p1);
    pp.lineTo(p2);
    pp.lineTo(p3);
    pp.lineTo(p4);

    return pp;
}

// 在线段l的起点画菱形，pp的终点在菱形的顶点
QPainterPath QRelationLine::diamondPath(const QLineF &l) const
{
    const qreal DiamondAngle = 25.0;
    const qreal DiamondLength = 8.0;

    // 找出菱形的四个顶点
    QLineF l2(l);
    QPointF p3 = l2.p1();
    l2.setLength(DiamondLength);
    l2.setAngle(l.angle() - DiamondAngle);
    QPointF p4 = l2.p2();
    QLineF l3(l2);
    l3.setAngle(l.angle() + DiamondAngle);
    QPointF p2 = l3.p2();
    l3.translate(l2.dx(), l2.dy());
    QPointF p1 = l3.p2();

    // 画菱形，注意pp终点的位置
    QPainterPath pp;
    pp.moveTo(p1);
    pp.lineTo(p2);
    pp.lineTo(p3);
    pp.lineTo(p4);
    pp.lineTo(p1);

    return pp;
}

QPainterPath QRelationLine::path() const
{
    QLineF l(m_p2, m_p1);
    QLineF l2(m_p1, m_p2);

//    QPainterPath pp = arrowPath(l);
//    QPainterPath pp2 = arrowPath(l2);
//    QPainterPath pp = trianglePath(l);
//    QPainterPath pp2 = trianglePath(l2);
    QPainterPath pp = diamondPath(l2);
    QPainterPath pp2 = diamondPath(l);
    pp.connectPath(pp2);

    return pp;
}

QRelationLine::QRelationLine(QGraphicsItem* parent)
    : QGraphicsItem(parent)
{

}

void QRelationLine::setLine(const QPointF &p1, const QPointF &p2)
{
    m_p1 = p1;
    m_p2 = p2;
}

QRectF QRelationLine::boundingRect() const
{
    return QRectF(m_p1, m_p2).adjusted(-1.0, -1.0, 1.0, 1.0);
}

void QRelationLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath pp = path();
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPath(pp);

    QPainterPathStroker pps;
    pps.setWidth(5);
    QPainterPath pp2 = pps.createStroke(pp);
//    painter->setPen(QPen(Qt::red, 0.5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
//    painter->setBrush(QBrush(QColor(0, 160, 0, 120)));
//    pp2.setFillRule(Qt::WindingFill);
//    painter->drawPath(pp2);

    QPainterPath pp3 = pp2.simplified();
    painter->setPen(QPen(Qt::blue, 0.5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QBrush(QColor(0, 160, 0, 120)));
    painter->drawPath(pp3);
/*
    QPolygonF poly = pp2.toFillPolygon();
    painter->setPen(QPen(Qt::red, 0.5, Qt::DotLine, Qt::RoundCap,Qt::RoundJoin));
    painter->setBrush(QBrush(QColor(0, 160, 0, 120)));
    painter->drawPolygon(poly);


    painter->setPen(QPen(Qt::blue, 0.5, Qt::DotLine, Qt::RoundCap,Qt::RoundJoin));
    painter->drawRect(pp2.boundingRect());

    painter->setPen(QPen(Qt::red, 0.5, Qt::DotLine, Qt::RoundCap,Qt::RoundJoin));
    painter->drawRect(pp.boundingRect());
*/
}




void QBrokenLine::route()
{
    const qreal MinLength = 10.0;
    auto extendPoint = [](int angle, const QPointF& p, QSizeF extend) {
        QPointF pReturn;
        switch (angle) {
        case 0:
            return QPointF(p.x() + extend.width(), p.y());
            break;
        case 90:
            return QPointF(p.x(), p.y() - extend.height());
            break;
        case 180:
            return QPointF(p.x() - extend.width(), p.y());
            break;
        case 270:
            return QPointF(p.x(), p.y() + extend.height());
            break;
        default:
            Q_ASSERT(false);
        }
    };

    qreal y, x;
    QSizeF extend(MinLength, MinLength);
    QPointF fromExtend = extendPoint(m_fromAngle, m_fromPoint, extend);
    QPointF toExtend = extendPoint(m_toAngle, m_toPoint, extend);

    if (m_fromAngle == 0 && m_toAngle == 0) {
        x = qMax(m_fromPoint.x(), m_toPoint.x()) + MinLength;
        m_points.push_back(QPointF(x, m_fromPoint.y()));
        m_points.push_back(QPointF(x, m_toPoint.y()));
    } else if(m_fromAngle == 0 && m_toAngle == 180) {
        if (m_fromPoint.x() > m_toPoint.x()) {
            y = (m_fromPoint.y() + m_toPoint.y()) / 2;
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(fromExtend.x(), y));
            m_points.push_back(QPointF(toExtend.x(), y));
            m_points.push_back(toExtend);
        } else {
            x = (m_fromPoint.x() + m_toPoint.x()) / 2;
            m_points.push_back(QPointF(x, m_fromPoint.y()));
            m_points.push_back(QPointF(x, m_toPoint.y()));
        }
    } else if (m_fromAngle == 0 && (m_toAngle == 90 || m_toAngle == 270)) {
        if ((m_toAngle ==  90 && m_fromPoint.x() < m_toPoint.x() && m_fromPoint.y() < m_toPoint.y())
         || (m_toAngle == 270 && m_fromPoint.x() < m_toPoint.x() && m_fromPoint.y() > m_toPoint.y())) {
            m_points.push_back(QPointF(m_toPoint.x(), m_fromPoint.y()));
        } else {
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(fromExtend.x(), toExtend.y()));
            m_points.push_back(toExtend);
        }
    } else if (m_fromAngle == 90 && m_toAngle == 90) {
        y = qMin(m_fromPoint.y(), m_toPoint.y()) - MinLength;
        m_points.push_back(QPointF(m_fromPoint.x(), y));
        m_points.push_back(QPointF(m_toPoint.x(), y));
    } else if (m_fromAngle == 90 && m_toAngle == 270) {
        if (m_fromPoint.y() < m_toPoint.y()) {
            x = (m_fromPoint.x() + m_toPoint.x()) / 2;
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(x, fromExtend.y()));
            m_points.push_back(QPointF(x, toExtend.y()));
            m_points.push_back(toExtend);
        } else {
            y = (m_fromPoint.y() + m_toPoint.y()) / 2;
            m_points.push_back(QPointF(m_fromPoint.x(), y));
            m_points.push_back(QPointF(m_toPoint.x(), y));
        }
    } else if (m_fromAngle == 90 && (m_toAngle == 0 || m_toAngle == 180)) {
        if ((m_toAngle ==   0 && m_fromPoint.y() > m_toPoint.y() && m_fromPoint.x() > m_toPoint.x())
         || (m_toAngle == 180 && m_fromPoint.y() > m_toPoint.y() && m_fromPoint.x() < m_toPoint.x())) {
            m_points.push_back(QPointF(m_fromPoint.x(), m_toPoint.y()));
        } else {
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(toExtend.x(), fromExtend.y()));
            m_points.push_back(toExtend);
        }
    } else if (m_fromAngle == 180 && m_toAngle == 180) {
        x = qMin(m_fromPoint.x(), m_toPoint.x()) - MinLength;
        m_points.push_back(QPointF(x, m_fromPoint.y()));
        m_points.push_back(QPointF(x, m_toPoint.y()));
    } else if (m_fromAngle == 180 && m_toAngle == 0) {
        if (m_fromPoint.x() < m_toPoint.x()) {
            y = (m_fromPoint.y() + m_toPoint.y()) / 2;
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(fromExtend.x(), y));
            m_points.push_back(QPointF(toExtend.x(), y));
            m_points.push_back(toExtend);
        } else {
            x = (m_fromPoint.x() + m_toPoint.x()) / 2;
            m_points.push_back(QPointF(x, m_fromPoint.y()));
            m_points.push_back(QPointF(x, m_toPoint.y()));
        }
    } else if (m_fromAngle == 180 && (m_toAngle == 90 || m_toAngle == 270)) {
        if ((m_toAngle == 90  && m_fromPoint.x() > m_toPoint.x() && m_fromPoint.y() < m_toPoint.y())
         || (m_toAngle == 270 && m_fromPoint.x() > m_toPoint.x() && m_fromPoint.y() > m_toPoint.y())) {
            m_points.push_back(QPointF(m_toPoint.x(), m_fromPoint.y()));
        } else {
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(fromExtend.x(), toExtend.y()));
            m_points.push_back(toExtend);
        }
    } else if (m_fromAngle == 270 && m_toAngle == 270) {
        y = qMax(m_fromPoint.y(), m_toPoint.y()) + MinLength;
        m_points.push_back(QPointF(m_fromPoint.x(), y));
        m_points.push_back(QPointF(m_toPoint.x(), y));
    } else if (m_fromAngle == 270 && m_toAngle == 90) {
        if (m_fromPoint.y() > m_toPoint.y()) {
            x = (m_fromPoint.x() + m_toPoint.x()) / 2;
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(x, fromExtend.y()));
            m_points.push_back(QPointF(x, toExtend.y()));
            m_points.push_back(toExtend);
        } else {
            y = (m_fromPoint.y() + m_toPoint.y()) / 2;
            m_points.push_back(QPointF(m_fromPoint.x(), y));
            m_points.push_back(QPointF(m_toPoint.x(), y));
        }
    } else if (m_fromAngle == 270 && (m_toAngle == 180 || m_toAngle == 0)) {
        if ((m_toAngle ==   0 && m_fromPoint.y() < m_toPoint.y() && m_fromPoint.x() > m_toPoint.x())
         || (m_toAngle == 180 && m_fromPoint.y() < m_toPoint.y() && m_fromPoint.x() < m_toPoint.x())) {
            m_points.push_back(QPointF(m_fromPoint.x(), m_toPoint.y()));
        } else {
            m_points.push_back(fromExtend);
            m_points.push_back(QPointF(toExtend.x(), fromExtend.y()));
            m_points.push_back(toExtend);
        }
    } else {
        Q_ASSERT(false);
    }

}

QPainterPath QBrokenLine::path() const
{
    QPainterPath pp;
    pp.moveTo(m_fromPoint);
    for (QPointF p: m_points) {
        pp.lineTo(p);
    }
    pp.lineTo(m_toPoint);

    QFont font = qApp->font();
//    pp.addText(m_fromPoint, font, QStringLiteral("from"));
//    pp.addText(m_toPoint, font, QString("to"));
    return pp;
}

QBrokenLine::QBrokenLine(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

void QBrokenLine::setAnglePoints(int fromA, const QPointF &fromP, int toA, const QPointF &toP)
{
    m_fromAngle = fromA;
    m_toAngle = toA;

    m_fromPoint = fromP;
    m_toPoint = toP;

    route();
}

QRectF QBrokenLine::boundingRect() const
{
    QPainterPath pp = path();
    return pp.boundingRect();
}

void QBrokenLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath pp = path();
    painter->drawPath(pp);

//    painter->setPen(QPen(Qt::green, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
//    painter->drawRect(boundingRect());
}
