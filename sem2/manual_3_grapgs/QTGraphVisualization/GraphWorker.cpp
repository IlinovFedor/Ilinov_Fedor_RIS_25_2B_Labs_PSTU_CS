//
// Created by localuser on 5/12/26.
//

#include "GraphWorker.h"

#include <QGraphicsView>
#include <QVBoxLayout>

void GraphWorker::draw_tree() {
    
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

void GraphWorker::draw_graph() {
    scene->clear();
    for (auto *v: vertices) delete v;
    for (auto *e: edges) delete e;
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
    std::function<void(int, int)> assign_x = [&](int v, int depth) {
        y_pos[v] = depth * V_STEP + 60.0;
        if (children[v].empty()) {
            x_pos[v] = leaf_counter * H_STEP + 60.0;
            leaf_counter++;
        } else {
            for (int c: children[v])
                assign_x(c, depth + 1);
            x_pos[v] = (x_pos[children[v].front()] + x_pos[children[v].back()]) / 2.0;
        }
    };
    assign_x(root, 0);

    // --- 4. Создаём вершины ---
    for (int i = 0; i < n; i++) {
        auto *v = new UiVertex(i);
        v->set_pos(x_pos[i], y_pos[i]);
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
