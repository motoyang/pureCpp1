//#include <QApplication>
//#include <qscreen.h>
//#include <qdebug.h>
//#include "qgraphicsscene.h"
//#include "qgraphicsview.h"
//#include "widget.h"
//#include "precompiled.h"
#include "qrelationline.h"

void test1(QGraphicsScene *s)
{
    qreal y = 0;
    QVector<QLineF> vl = {
        QLineF(30, 30, 70, 70),
        QLineF(30, 70, 70, 30),
        QLineF(70, 30, 30, 70),
        QLineF(70, 70, 30, 30)
    };
    for (const QLineF& line: vl) {
        QString str = QString("p1(%1, %2), p2(%3, %4)")
                .arg(line.p1().x())
                .arg(line.p1().y())
                .arg(line.p2().x())
                .arg(line.p2().y());
        auto item = new QGraphicsSimpleTextItem(str);
        item->setPos(0, y);
        s->addItem(item);
        y += item->boundingRect().height();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QBrokenLine *l = new QBrokenLine();
                l->setAngle(i * 90, j * 90);
                l->setPoints(line.p1(), line.p2());
                l->setPos(j * 100, y + i * 100);
                s->addItem(l);

                str = QString("fA=%1, tA=%2")
                        .arg(i*90)
                        .arg(j*90);
                item = new QGraphicsSimpleTextItem(str);
                item->setPos(j * 100, y + i * 100 + 100);
                s->addItem(item);

                auto r = new QGraphicsRectItem(0, 0, 100, 100 + item->boundingRect().height());
                r->setPen(QPen(Qt::blue, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
                r->setPos(j * 100, y + i * 100);
                s->addItem(r);
            }
            y += item->boundingRect().height();
        }
        y += 400 + 20;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    QScreen *q = a.primaryScreen();
    qreal dpi = q->logicalDotsPerInch() / 72;
    qreal ppi = q->physicalDotsPerInch() / 72;
    qDebug() << dpi;
    qDebug() << ppi;

    QPixmap pixmap(5, 5);
    pixmap.fill();
    QPainter painter(&pixmap);
    QPen pen(Qt::lightGray, 0.1);
    painter.setPen(pen);
    painter.drawLine(0, 0, 0, 4);
    painter.drawLine(1, 0, 4, 0);
    painter.end();

    auto scene = new QGraphicsScene(0.5, 0.5, 600, 6000);
//    scene->setBackgroundBrush(Qt::CrossPattern);
    scene->setBackgroundBrush(QBrush(pixmap));

//    scene->setForegroundBrush(QColor(0, 160, 0, 20));
//    scene->addRect(20, 10, dpi * 300, dpi * 1 * 72, QPen(Qt::green), QBrush(Qt::black));
//      QRelationLine* rl = new QRelationLine();

    test1(scene);
/*
    QBrokenLine* rl = new QBrokenLine();
    rl->setAngle(270, 270);
      rl->setPoints(QPointF(0, 15), QPointF(35, 80));
      rl->setPos(50.5, 50.5);
      scene->addItem(rl);
*/
    auto view = std::make_shared<QGraphicsView>();
    view->setScene(scene);
    view->scale(ppi/dpi, ppi/dpi);
    view->show();

    return a.exec();
}
