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

    bool is_active = false;
    bool is_used = false;
public:
    UiVertex(std::string value = "0");

    void set_pos(qreal x, qreal y);
    void set_value(std::string value);
    const qreal get_radius();

    void activate();
    void dis_activate();
    void set_used();
    void set_unused();

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif //QTGRAPHVISUALIZATION_UIVERTEX_H
