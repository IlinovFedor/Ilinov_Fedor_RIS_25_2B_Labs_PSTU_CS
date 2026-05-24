#include "GraphWorker.h"

#include <QVBoxLayout>
#include <QGraphicsLineItem>
#include <QString>
#include <algorithm>

GraphWorker::GraphWorker(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setRenderHint(QPainter::Antialiasing);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setInteractive(true);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GraphWorker::~GraphWorker() {
    for (auto *v : vertices) delete v;
}

std::string GraphWorker::key_str(double key) {
    QString s = QString::number(key, 'f', 2);
    while (s.contains('.') && (s.endsWith('0') || s.endsWith('.')))
        s.chop(1);
    return s.toStdString();
}

void GraphWorker::compute_positions(Node *node, int depth, int &index,
                                     std::unordered_map<Node *, double> &x_pos,
                                     std::unordered_map<Node *, double> &y_pos) {
    if (!node) return;
    const double H_STEP = 200.0;
    const double V_STEP = 200.0;

    compute_positions(node->left, depth + 1, index, x_pos, y_pos);
    x_pos[node] = index * H_STEP + 60.0;
    y_pos[node] = depth * V_STEP + 60.0;
    index++;
    compute_positions(node->right, depth + 1, index, x_pos, y_pos);
}

void GraphWorker::draw_tree() {
    scene->clear();
    vertices.clear();
    node_vertex_map.clear();

    if (!tree.getRoot()) return;

    std::unordered_map<Node *, double> x_pos, y_pos;
    int index = 0;
    compute_positions(tree.getRoot(), 0, index, x_pos, y_pos);

    double min_x = 1e9, max_x = -1e9, min_y = 1e9, max_y = -1e9;
    for (auto &[node, x] : x_pos) {
        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y_pos[node]);
        max_y = std::max(max_y, y_pos[node]);
    }

    QPointF center = view->mapToScene(view->viewport()->rect().center());
    double shift_x = center.x() - (min_x + max_x) / 2.0;
    double shift_y = center.y() - (min_y + max_y) / 2.0;

    std::function<void(Node *)> draw_edges = [&](Node *node) {
        if (!node) return;
        if (node->left) {
            auto *line = scene->addLine(
                x_pos[node] + shift_x, y_pos[node] + shift_y,
                x_pos[node->left] + shift_x, y_pos[node->left] + shift_y,
                QPen(Qt::black, 3));
            line->setZValue(-1);
        }
        if (node->right) {
            auto *line = scene->addLine(
                x_pos[node] + shift_x, y_pos[node] + shift_y,
                x_pos[node->right] + shift_x, y_pos[node->right] + shift_y,
                QPen(Qt::black, 3));
            line->setZValue(-1);
        }
        draw_edges(node->left);
        draw_edges(node->right);
    };
    draw_edges(tree.getRoot());

    std::function<void(Node *)> draw_vertices = [&](Node *node) {
        if (!node) return;
        auto *v = new UiVertex(key_str(node->key));
        v->set_pos(x_pos[node] + shift_x, y_pos[node] + shift_y);
        scene->addItem(v);
        vertices.push_back(v);
        node_vertex_map[node] = v;
        draw_vertices(node->left);
        draw_vertices(node->right);
    };
    draw_vertices(tree.getRoot());
}

void GraphWorker::draw() {
    draw_tree();
}

void GraphWorker::zoom_in() {
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    view->scale(1.2, 1.2);
}

void GraphWorker::zoom_out() {
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    view->scale(1.0 / 1.2, 1.0 / 1.2);
}

void GraphWorker::insert_prepare(double key) {
    steps.clear();
    step = 0;

    if (!tree.getRoot()) {
        tree.insert(key);
        draw();
        return;
    }

    std::vector<Node *> path;
    Node *current = tree.getRoot();
    while (current) {
        path.push_back(current);
        if (key < current->key) {
            if (!current->left) break;
            current = current->left;
        } else if (key > current->key) {
            if (!current->right) break;
            current = current->right;
        } else {
            break;
        }
    }

    for (size_t i = 0; i < path.size(); i++) {
        Node *node = path[i];
        if (i == 0) {
            steps.push_back([this, node]() {
                if (node_vertex_map.count(node))
                    node_vertex_map[node]->make_red();
            });
        } else {
            Node *prev = path[i - 1];
            steps.push_back([this, prev, node]() {
                if (prev && node_vertex_map.count(prev))
                    node_vertex_map[prev]->make_blue();
                if (node && node_vertex_map.count(node))
                    node_vertex_map[node]->make_red();
            });
        }
    }

    steps.push_back([this, key]() {
        tree.insert(key);
        draw();
    });
}

void GraphWorker::remove_prepare(double key) {
    steps.clear();
    step = 0;

    Node *current = tree.getRoot();
    if (!current) return;

    Node *prev = nullptr;
    while (current) {
        steps.push_back([this, current, prev]() {
            if (prev && node_vertex_map.count(prev))
                node_vertex_map[prev]->make_blue();
            if (current && node_vertex_map.count(current))
                node_vertex_map[current]->make_red();
        });
        prev = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            break;
    }

    steps.push_back([this, key]() {
        tree.remove(key);
        draw();
    });
}

void GraphWorker::search_prepare(double key) {
    steps.clear();
    step = 0;

    Node *current = tree.getRoot();
    if (!current) return;

    Node *prev = nullptr;
    while (current) {
        steps.push_back([this, current, prev]() {
            if (prev && node_vertex_map.count(prev))
                node_vertex_map[prev]->make_blue();
            if (current && node_vertex_map.count(current))
                node_vertex_map[current]->make_red();
        });
        prev = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            break;
    }

    if (current && current->key == key) {
        steps.push_back([this, current]() {
            if (current && node_vertex_map.count(current))
                node_vertex_map[current]->make_green();
        });
    } else {
        steps.push_back([this, prev]() {
            if (prev && node_vertex_map.count(prev))
                node_vertex_map[prev]->make_green();
        });
    }
}

void GraphWorker::find_min_prepare() {
    steps.clear();
    step = 0;

    Node *current = tree.getRoot();
    if (!current) return;

    Node *prev = nullptr;
    while (current) {
        steps.push_back([this, current, prev]() {
            if (prev && node_vertex_map.count(prev))
                node_vertex_map[prev]->make_blue();
            if (current && node_vertex_map.count(current))
                node_vertex_map[current]->make_red();
        });
        prev = current;
        current = current->left;
    }

    steps.push_back([this, min_node = prev]() {
        if (min_node && node_vertex_map.count(min_node))
            node_vertex_map[min_node]->make_green();
    });
}

void GraphWorker::traversal_prepare(const std::vector<double> &order) {
    steps.clear();
    step = 0;
    if (order.empty()) return;

    for (auto &[node, vertex] : node_vertex_map)
        vertex->make_black();

    steps.push_back([this, key = order[0]]() {
        Node *node = tree.search(key);
        if (node && node_vertex_map.count(node))
            node_vertex_map[node]->make_red();
    });

    for (size_t i = 1; i < order.size(); i++) {
        double prev_key = order[i - 1];
        double curr_key = order[i];
        steps.push_back([this, prev_key, curr_key]() {
            Node *prev_node = tree.search(prev_key);
            Node *curr_node = tree.search(curr_key);
            if (prev_node && node_vertex_map.count(prev_node))
                node_vertex_map[prev_node]->make_blue();
            if (curr_node && node_vertex_map.count(curr_node))
                node_vertex_map[curr_node]->make_red();
        });
    }

    steps.push_back([this, key = order.back()]() {
        Node *node = tree.search(key);
        if (node && node_vertex_map.count(node))
            node_vertex_map[node]->make_green();
    });
}

void GraphWorker::balance_tree() {
    tree.balance();
    draw();
}

void GraphWorker::step_next() {
    if (step >= static_cast<int>(steps.size())) return;
    steps[step]();
    step++;
}

void GraphWorker::reset() {
    steps.clear();
    step = 0;
    for (auto &[node, vertex] : node_vertex_map)
        vertex->make_black();
}
