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

    return QRectF(aleft, atop, awidth, aheight);
}

static QColor color_for_dir(UiEdge::DirColor c) {
    switch (c) {
        case UiEdge::DirColor::Included: return Qt::green;
        case UiEdge::DirColor::Excluded: return Qt::blue;
        case UiEdge::DirColor::Current:  return Qt::red;
        default: return Qt::black;
    }
}

void UiEdge::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *,
                   QWidget *) {
    if (i_vertex->pos() == j_vertex->pos()) return;

    DirColor effective = DirColor::None;
    if (i_j_color == DirColor::Current || j_i_color == DirColor::Current)
        effective = DirColor::Current;
    else if (i_j_color == DirColor::Included || j_i_color == DirColor::Included)
        effective = DirColor::Included;
    else if (i_j_color == DirColor::Excluded || j_i_color == DirColor::Excluded)
        effective = DirColor::Excluded;

    QColor line_color = Qt::black;
    int line_width = 3;
    if (effective == DirColor::Current || is_active_i_j || is_active_j_i) {
        line_color = Qt::red;
        line_width = 5;
    } else if (effective == DirColor::Included) {
        line_color = Qt::green;
        line_width = 5;
    } else if (effective == DirColor::Excluded) {
        line_color = Qt::blue;
        line_width = 3;
    }
    painter->setPen(QPen(line_color, line_width));
    painter->drawLine(i_vertex->pos(), j_vertex->pos());

    auto pen_for_dir = [&](DirColor c, bool active) {
        if (active) return QPen(Qt::red, 5);
        return QPen(color_for_dir(c), 3);
    };

    if (i_j_weight != nullptr) {
        QPolygonF arrow = build_arrow(i_vertex->pos(), j_vertex->pos(),
                                      i_vertex->get_radius() * 2, i_vertex->get_radius());
        painter->setPen(pen_for_dir(i_j_color, is_active_i_j));
        painter->setBrush(QBrush(Qt::white));
        painter->drawPolygon(arrow);

        QPointF centroid = (arrow[0] + arrow[1] + arrow[2]) / 3.0;
        painter->setPen(QPen(Qt::black));
        QString text = QString::number(*this->i_j_weight);
        if (*i_j_weight == INT_MAX) text = "+inf";
        if (*i_j_weight == INT_MIN) text = "-inf";
        painter->drawText((int)(centroid.x() - 20), (int)(centroid.y() - 10),
                          40, 20, Qt::AlignCenter, text);
    }

    if (j_i_weight != nullptr) {
        QPolygonF arrow = build_arrow(j_vertex->pos(), i_vertex->pos(),
                                      i_vertex->get_radius() * 2, i_vertex->get_radius());
        painter->setPen(pen_for_dir(j_i_color, is_active_j_i));
        painter->setBrush(QBrush(Qt::white));
        painter->drawPolygon(arrow);

        QPointF centroid = (arrow[0] + arrow[1] + arrow[2]) / 3.0;
        painter->setPen(QPen(Qt::black));
        QString text = QString::number(*this->j_i_weight);
        if (*j_i_weight == INT_MAX) text = "+inf";
        if (*j_i_weight == INT_MIN) text = "-inf";
        painter->drawText((int)(centroid.x() - 20), (int)(centroid.y() - 10),
                          40, 20, Qt::AlignCenter, text);
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

void UiEdge::set_i_j_weight(int *weight) { i_j_weight = weight; update(); }
void UiEdge::set_j_i_weight(int *weight) { j_i_weight = weight; update(); }

void UiEdge::activate_i_j() { is_active_i_j = true; update(); }
void UiEdge::dis_activate_i_j() { is_active_i_j = false; update(); }
void UiEdge::activate_j_i() { is_active_j_i = true; update(); }
void UiEdge::dis_activate_j_i() { is_active_j_i = false; update(); }

void UiEdge::reset_colors() { i_j_color = DirColor::None; j_i_color = DirColor::None; update(); }
void UiEdge::set_i_j_color(DirColor c) { i_j_color = c; update(); }
void UiEdge::set_j_i_color(DirColor c) { j_i_color = c; update(); }

int *UiEdge::get_i_j_weight() { return i_j_weight; }
int *UiEdge::get_j_i_weight() { return j_i_weight; }
