//
// Created by localuser on 5/12/26.
//

#include "UiVertex.h"

UiVertex::UiVertex(std::string value) {
    vertex_label = value;
}

QRectF UiVertex::boundingRect() const {
    return QRectF(-vertex_radius, -vertex_radius,
                  vertex_radius * 2,
                  vertex_radius * 2);
}

void UiVertex::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *,
                     QWidget *) {

    painter->setPen(QPen(Qt::black, 3));
    if (is_used)
        painter->setPen(QPen(Qt::blue, 5));
    if (is_active)
        painter->setPen(QPen(Qt::red, 5));

    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(boundingRect(),
                      Qt::AlignCenter,
                      QString::fromStdString(vertex_label));
}

void UiVertex::set_pos(qreal x, qreal y) {
    setPos(x, y);
}

void UiVertex::set_value(std::string value) {
    vertex_label = value;
    update();
}

const qreal UiVertex::get_radius() {
    return vertex_radius;
}

void UiVertex::activate() {
    is_active = true;
}

void UiVertex::dis_activate() {
    is_active = false;
}

void UiVertex::set_used() {
    is_used = true;
}

void UiVertex::set_unused() {
    is_used = false;
}
