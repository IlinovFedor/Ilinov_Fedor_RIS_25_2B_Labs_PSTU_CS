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
    painter->setPen(is_active_i_j || is_active_j_i ? QPen(Qt::red, 5) : QPen(Qt::black, 3));
    painter->drawLine(i_vertex->pos(), j_vertex->pos());


    if (i_j_weight != nullptr) {
        QPolygonF arrow = build_arrow(i_vertex->pos(), j_vertex->pos(), i_vertex->get_radius() * 2, i_vertex->get_radius());

        painter->setPen(is_active_i_j ? QPen(Qt::red, 5) : QPen(Qt::black, 3));
        painter->setBrush(QBrush(Qt::white));
        painter->drawPolygon(arrow);

        QPointF centroid = (arrow[0] + arrow[1] + arrow[2]) / 3.0;
        painter->setPen(QPen(Qt::black));
        painter->drawText(
            (int)(centroid.x() - 20),
            (int)(centroid.y() - 10),
            40, 20,
            Qt::AlignCenter,
            QString::number(*this->i_j_weight)
        );
    }

    if (j_i_weight != nullptr) {
        QPolygonF arrow = build_arrow(j_vertex->pos(), i_vertex->pos(), i_vertex->get_radius() * 2, i_vertex->get_radius());

        painter->setPen(is_active_j_i ? QPen(Qt::red, 5) : QPen(Qt::black, 3));
        painter->setBrush(QBrush(Qt::white));
        painter->drawPolygon(arrow);

        QPointF centroid = (arrow[0] + arrow[1] + arrow[2]) / 3.0;
        painter->setPen(QPen(Qt::black));
        painter->drawText(
            (int)(centroid.x() - 20),
            (int)(centroid.y() - 10),
            40, 20,
            Qt::AlignCenter,
            QString::number(*this->j_i_weight)
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

    QPointF tip   = to - unit * offset;
    QPointF base1 = tip - unit * height + perp * (size / 2.0);
    QPointF base2 = tip - unit * height - perp * (size / 2.0);

    return QPolygonF() << tip << base1 << base2;
}

void UiEdge::set_i_j_weight(int *weight) {
    i_j_weight = weight;
}

void UiEdge::set_j_i_weight(int *weight) {
    j_i_weight = weight;
}

void UiEdge::activate_i_j() {
    is_active_i_j = true;
}

void UiEdge::dis_activate_i_j() {
    is_active_i_j = false;
}


void UiEdge::activate_j_i() {
    is_active_j_i = true;
}

void UiEdge::dis_activate_j_i() {
    is_active_j_i = false;
}