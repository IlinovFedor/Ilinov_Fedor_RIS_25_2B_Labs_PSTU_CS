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

    painter->setPen(pen);

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

void UiVertex::make_red() {
    pen = QPen(Qt::red, 5);
    update();
}
void UiVertex::make_blue() {
    pen = QPen(Qt::blue, 5);
    update();
}
void UiVertex::make_green() {
    pen = QPen(Qt::green, 3 );
    update();
}

void UiVertex::make_black() {
    pen = QPen(Qt::black, 3);
    update();
}
