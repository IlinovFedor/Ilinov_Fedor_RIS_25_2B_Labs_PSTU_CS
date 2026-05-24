//
// Created by localuser on 5/12/26.
//

#include "UiEdge.h"

#include "UiVertex.h"

UiEdge::UiEdge(UiVertex *i, UiVertex *j) {
    i_vertex = i;
    j_vertex = j;
}

QRectF UiEdge::boundingRect() const {
    auto aleft = std::min(i_vertex->pos().x(), j_vertex->pos().x()) - i_vertex->get_radius();
    auto atop = std::min(i_vertex->pos().y(), j_vertex->pos().y()) - i_vertex->get_radius();
    auto awidth = abs(i_vertex->pos().x() - j_vertex->pos().x()) + 2 * i_vertex->get_radius();
    auto aheight = abs(i_vertex->pos().y() - j_vertex->pos().y()) + 2 * i_vertex->get_radius();

    return QRectF(aleft, atop,
                  awidth,
                  aheight);
}

void UiEdge::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
    if (i_vertex->pos() == j_vertex->pos())
        return;

    painter->setPen(is_active_i_j || is_active_j_i ? QPen(Qt::red, 5) : QPen(Qt::black, 3));
    painter->drawLine(i_vertex->pos(), j_vertex->pos());


    if (i_j_weight != nullptr) {
        QPolygonF arrow = build_arrow(i_vertex->pos(), j_vertex->pos(), i_vertex->get_radius() * 2,
                                      i_vertex->get_radius());

        painter->setPen(is_active_i_j ? QPen(Qt::red, 5) : QPen(Qt::black, 3));
        painter->setBrush(QBrush(Qt::white));
        painter->drawPolygon(arrow);

        QPointF centroid = (arrow[0] + arrow[1] + arrow[2]) / 3.0;
        painter->setPen(QPen(Qt::black));
        QString text = QString::number(*this->i_j_weight);
        if (*i_j_weight == INT_MAX)
            text = "+inf";
        if (*i_j_weight == INT_MIN)
            text = "-inf";
        painter->drawText(
            (int) (centroid.x() - 20),
            (int) (centroid.y() - 10),
            40, 20,
            Qt::AlignCenter,
            text
        );
    }

    if (j_i_weight != nullptr) {
        QPolygonF arrow = build_arrow(j_vertex->pos(), i_vertex->pos(), i_vertex->get_radius() * 2,
                                      i_vertex->get_radius());

        painter->setPen(is_active_j_i ? QPen(Qt::red, 5) : QPen(Qt::black, 3));
        painter->setBrush(QBrush(Qt::white));
        painter->drawPolygon(arrow);

        QPointF centroid = (arrow[0] + arrow[1] + arrow[2]) / 3.0;
        painter->setPen(QPen(Qt::black));
        QString text = QString::number(*this->j_i_weight);
        if (*j_i_weight == INT_MAX)
            text = "+inf";
        if (*j_i_weight == INT_MIN)
            text = "-inf";
        painter->drawText(
            (int) (centroid.x() - 20),
            (int) (centroid.y() - 10),
            40, 20,
            Qt::AlignCenter,
            text
        );
    }
}

QPolygonF UiEdge::build_arrow(const QPointF &from, const QPointF &to,
                              double size, double offset) {
    QPointF dir = to - from;
    double len = std::sqrt(dir.x() * dir.x() + dir.y() * dir.y());
    if (len == 0) return QPolygonF();

    QPointF unit = dir / len;
    QPointF perp(-unit.y(), unit.x());

    double height = size * std::sqrt(3.0) / 2.0;

    QPointF tip = to - unit * offset;
    QPointF base1 = tip - unit * height + perp * (size / 2.0);
    QPointF base2 = tip - unit * height - perp * (size / 2.0);
    QPolygonF pol;
    pol.resize(3);
    pol[0] = tip;
    pol[1] = base1;
    pol[2] = base2;
    return pol;
}

void UiEdge::set_i_j_weight(int *weight) {
    i_j_weight = weight;
    update();
}

void UiEdge::set_j_i_weight(int *weight) {
    j_i_weight = weight;
    update();
}

void UiEdge::activate_i_j() {
    is_active_i_j = true;
    update();
}

void UiEdge::dis_activate_i_j() {
    is_active_i_j = false;
    update();
}

void UiEdge::activate_j_i() {
    is_active_j_i = true;
    update();
}

void UiEdge::dis_activate_j_i() {
    is_active_j_i = false;
    update();
}

int *UiEdge::get_i_j_weight() { return i_j_weight; }

int *UiEdge::get_j_i_weight() { return j_i_weight; }
