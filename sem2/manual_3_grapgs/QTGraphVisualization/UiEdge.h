//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_UIEDGE_H
#define QTGRAPHVISUALIZATION_UIEDGE_H
#include <QGraphicsItem>
#include "UiVertex.h"

class UiEdge : public QGraphicsItem {
    UiVertex *i_vertex;
    UiVertex *j_vertex;
    int* i_j_weight = nullptr;
    int* j_i_weight = nullptr;
    bool is_active_i_j = false;
    bool is_active_j_i = false;
    bool is_used_i_j = false;
    bool is_used_j_i = false;
    QPolygonF build_arrow(const QPointF &from, const QPointF &to, double size, double offset);


public:
    UiEdge(UiVertex *i, UiVertex *j);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void set_i_j_weight(int* weight);
    void set_j_i_weight(int* weight);

    void activate_i_j();
    void dis_activate_i_j();

    void activate_j_i();
    void dis_activate_j_i();

    int* get_i_j_weight();;
    int* get_j_i_weight();;
};

#endif //QTGRAPHVISUALIZATION_UIEDGE_H
