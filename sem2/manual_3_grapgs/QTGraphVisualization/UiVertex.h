//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_UIVERTEX_H
#define QTGRAPHVISUALIZATION_UIVERTEX_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

class UiVertex : public QGraphicsItem {
    std::string vertex_label = "0";
    qreal vertex_radius = 30;

    QColor color = Qt::black;
    QPen pen = QPen(Qt::black, 3);
public:
    UiVertex(std::string value = "0");

    void set_pos(qreal x, qreal y);
    void set_value(std::string value);
    const qreal get_radius();

    void make_red();
    void make_green();
    void make_blue();
    void make_black();
    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif //QTGRAPHVISUALIZATION_UIVERTEX_H
