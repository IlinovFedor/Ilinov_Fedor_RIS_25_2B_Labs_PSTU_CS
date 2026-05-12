//
// Created by localuser on 5/12/26.
//

#include "GraphWorker.h"

#include <QGraphicsView>
#include <QVBoxLayout>
#include <cmath>

namespace {
void assign_tree_positions(int v,
                           int depth,
                           const std::vector<std::vector<int> > &children,
                           std::vector<double> &x_pos,
                           std::vector<double> &y_pos,
                           int &leaf_counter,
                           double h_step,
                           double v_step) {
    y_pos[v] = depth * v_step + 60.0;
    if (children[v].empty()) {
        x_pos[v] = leaf_counter * h_step + 60.0;
        leaf_counter++;
        return;
    }

    for (int c : children[v])
        assign_tree_positions(c, depth + 1, children, x_pos, y_pos, leaf_counter, h_step, v_step);

    x_pos[v] = (x_pos[children[v].front()] + x_pos[children[v].back()]) / 2.0;
}
}

void GraphWorker::draw_tree() {
    scene->clear();
    vertices.clear();
    edges.clear();

    int n = graph.size();
    if (n == 0) return;

    // --- 1. Корень: вершина без входящих рёбер ---
    std::vector<int> in_degree(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && graph.has_edge(i, j))
                in_degree[j]++;

    int root = 0;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0) {
            root = i;
            break;
        }

    // --- 2. BFS: строим дерево ---
    std::vector<std::vector<int> > children(n);
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(root);
    visited[root] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next = 0; next < n; next++) {
            if (!visited[next] && graph.has_edge(cur, next)) {
                visited[next] = true;
                children[cur].push_back(next);
                q.push(next);
            }
        }
    }

    // --- 3. Расстановка координат ---
    const double H_STEP = 200.0;
    const double V_STEP = 200.0;

    std::vector<double> x_pos(n, 0.0);
    std::vector<double> y_pos(n, 0.0);

    int leaf_counter = 0;
    assign_tree_positions(root, 0, children, x_pos, y_pos, leaf_counter, H_STEP, V_STEP);

    double min_x = x_pos[0];
    double max_x = x_pos[0];
    double min_y = y_pos[0];
    double max_y = y_pos[0];
    for (int i = 1; i < n; i++) {
        min_x = std::min(min_x, x_pos[i]);
        max_x = std::max(max_x, x_pos[i]);
        min_y = std::min(min_y, y_pos[i]);
        max_y = std::max(max_y, y_pos[i]);
    }

    QPointF center = view->mapToScene(view->viewport()->rect().center());
    double shift_x = center.x() - (min_x + max_x) / 2.0;
    double shift_y = center.y() - (min_y + max_y) / 2.0;

    // --- 4. Создаём вершины ---
    for (int i = 0; i < n; i++) {
        auto *v = new UiVertex(i + 1);
        v->set_pos(x_pos[i] + shift_x, y_pos[i] + shift_y);
        vertices.push_back(v);
    }

    // --- 5. Создаём рёбра ---
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph.has_edge(i, j) || graph.has_edge(j, i)) {
                auto *e = new UiEdge(vertices[i], vertices[j]);
                if (graph.has_edge(i, j))
                    e->set_i_j_weight(graph.get_weight(i, j));
                if (graph.has_edge(j, i))
                    e->set_j_i_weight(graph.get_weight(j, i));
                edges.push_back(e);
            }
        }
    }

    for (auto edge : edges) scene->addItem(edge);
    for (auto vertex : vertices) scene->addItem(vertex);
}

void GraphWorker::draw_not_tree() {
    scene->clear();
    vertices.clear();
    edges.clear();

    int n = graph.size();
    if (n == 0) return;

    const double radius = 500.0;
    const double step = 2.0 * M_PI / n;
    QPointF center = view->mapToScene(view->viewport()->rect().center());

    for (int i = 0; i < n; i++) {
        double angle = step * i;
        double x = center.x() + radius * std::cos(angle);
        double y = center.y() + radius * std::sin(angle);
        auto *v = new UiVertex(i + 1);
        v->set_pos(x, y);
        vertices.push_back(v);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph.has_edge(i, j) || graph.has_edge(j, i)) {
                auto *e = new UiEdge(vertices[i], vertices[j]);
                if (graph.has_edge(i, j))
                    e->set_i_j_weight(graph.get_weight(i, j));
                if (graph.has_edge(j, i))
                    e->set_j_i_weight(graph.get_weight(j, i));
                edges.push_back(e);
            }
        }
    }

    for (auto edge : edges) scene->addItem(edge);
    for (auto vertex : vertices) scene->addItem(vertex);
}

GraphWorker::GraphWorker(QWidget *parent, const Graph &new_graph) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    graph = new_graph;

    view->setRenderHint(QPainter::Antialiasing);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setInteractive(true);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GraphWorker::~GraphWorker() {
    for (auto* v : vertices) delete v;
    for (auto* e : edges) delete e;
}

void GraphWorker::zoom_in() {
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    view->scale(1.2, 1.2);
}

void GraphWorker::zoom_out() {
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    view->scale(1.0 / 1.2, 1.0 / 1.2);
}

void GraphWorker::draw_graph() {
    if (graph.is_visual_tree()) {
        draw_tree();
        return;
    }
    draw_not_tree();
}
