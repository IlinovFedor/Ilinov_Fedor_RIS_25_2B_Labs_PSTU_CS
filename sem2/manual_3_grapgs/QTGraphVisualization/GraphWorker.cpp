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

void GraphWorker::clear_active_edges() {
    for (auto *edge : active_edges) {
        if (!edge) continue;
        edge->dis_activate_i_j();
        edge->dis_activate_j_i();
        edge->update();
    }
    active_edges.clear();
}

void GraphWorker::draw_tree() {
    scene->clear();
    vertices.clear();
    edges.clear();
    edge_matrix.clear();

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
        auto *v = new UiVertex(std::to_string(i + 1));
        v->set_pos(x_pos[i] + shift_x, y_pos[i] + shift_y);
        vertices.push_back(v);
    }

    edge_matrix.assign(n, std::vector<UiEdge*>(n, nullptr));

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
                if (graph.has_edge(i, j))
                    edge_matrix[i][j] = e;
                if (graph.has_edge(j, i))
                    edge_matrix[j][i] = e;
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
    edge_matrix.clear();

    int n = graph.size();
    if (n == 0) return;

    const double radius = 500.0;
    const double step = 2.0 * M_PI / n;
    QPointF center = view->mapToScene(view->viewport()->rect().center());

    for (int i = 0; i < n; i++) {
        double angle = step * i;
        double x = center.x() + radius * std::cos(angle);
        double y = center.y() + radius * std::sin(angle);
        auto *v = new UiVertex(std::to_string(i + 1));
        v->set_pos(x, y);
        vertices.push_back(v);
    }

    edge_matrix.assign(n, std::vector<UiEdge*>(n, nullptr));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph.has_edge(i, j) || graph.has_edge(j, i)) {
                auto *e = new UiEdge(vertices[i], vertices[j]);
                if (graph.has_edge(i, j))
                    e->set_i_j_weight(graph.get_weight(i, j));
                if (graph.has_edge(j, i))
                    e->set_j_i_weight(graph.get_weight(j, i));
                edges.push_back(e);
                if (graph.has_edge(i, j))
                    edge_matrix[i][j] = e;
                if (graph.has_edge(j, i))
                    edge_matrix[j][i] = e;
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

void GraphWorker::dfs_prepare(int start_index) {
    steps.clear();
    step_index = 0;
    last_dist.clear();
    active_edges.clear();

    int n = graph.size();
    if (n == 0) return;
    if (start_index < 0 || start_index >= n) return;

    std::vector<bool> visited(n, false);
    std::vector<int> parent(n, -1);

    struct Frame {
        int v;
        int next;
    };

    std::vector<Frame> stack;
    stack.push_back({start_index, 0});
    visited[start_index] = true;

    Step root_step;
    root_step.type = Step::VertexAdvance;
    root_step.cur_v = start_index;
    steps.push_back(root_step);

    while (!stack.empty()) {
        Frame &frame = stack.back();
        int v = frame.v;

        bool moved = false;
        for (int j = frame.next; j < n; j++) {
            frame.next = j + 1;
            if (graph.has_edge(v, j) && !visited[j]) {
                parent[j] = v;
                visited[j] = true;

                Step edge_step;
                edge_step.type = Step::EdgeActivate;
                edge_step.from = v;
                edge_step.to = j;
                steps.push_back(edge_step);

                Step vertex_step;
                vertex_step.type = Step::VertexAdvance;
                vertex_step.prev_v = v;
                vertex_step.cur_v = j;
                vertex_step.from = v;
                vertex_step.to = j;
                steps.push_back(vertex_step);

                stack.push_back({j, 0});
                moved = true;
                break;
            }
        }

        if (moved) continue;

        stack.pop_back();
        if (parent[v] != -1) {
            Step back_step;
            back_step.type = Step::VertexAdvance;
            back_step.prev_v = v;
            back_step.cur_v = parent[v];
            steps.push_back(back_step);
        }
    }
}

void GraphWorker::dfs_step_next() {
    if (step_index >= steps.size()) return;

    Step step = steps[step_index];
    step_index++;

    if (step.type == Step::DijkstraSelect) {
        for (auto *vertex : vertices) {
            vertex->dis_activate();
            vertex->update();
        }

        clear_active_edges();

        if (step.cur_v >= 0 && step.cur_v < static_cast<int>(vertices.size())) {
            vertices[step.cur_v]->set_used();
            vertices[step.cur_v]->activate();
            std::string label = std::to_string(step.cur_v + 1) + "\n" +
                                (step.dist >= 1000000000 ? "INF" : std::to_string(step.dist));
            vertices[step.cur_v]->set_value(label);
            vertices[step.cur_v]->update();
        }
        return;
    }

    if (step.type == Step::DijkstraInspect) {
        clear_active_edges();

        if (step.from >= 0 && step.from < static_cast<int>(vertices.size())) {
            for (auto *vertex : vertices) {
                vertex->dis_activate();
                vertex->update();
            }
            vertices[step.from]->activate();
            vertices[step.from]->update();
        }

        if (step.from >= 0 && step.to >= 0
            && step.from < static_cast<int>(edge_matrix.size())
            && step.to < static_cast<int>(edge_matrix.size())) {
            UiEdge *edge = edge_matrix[step.from][step.to];
            if (edge) {
                if (step.from < step.to)
                    edge->activate_i_j();
                else if (step.from > step.to)
                    edge->activate_j_i();
                edge->update();
                active_edges.push_back(edge);
            }
        }
        return;
    }

    if (step.type == Step::DijkstraRelax) {
        clear_active_edges();

        if (step.to >= 0 && step.to < static_cast<int>(vertices.size())) {
            for (auto *vertex : vertices) {
                vertex->dis_activate();
                vertex->update();
            }
            vertices[step.to]->activate();
            std::string label = std::to_string(step.to + 1) + "\n" +
                                (step.dist >= 1000000000 ? "INF" : std::to_string(step.dist));
            vertices[step.to]->set_value(label);
            vertices[step.to]->update();
        }
        return;
    }


    if (step.type == Step::EdgeActivate) {
        for (auto *vertex : vertices) {
            vertex->dis_activate();
            vertex->update();
        }

        if (step.from >= 0 && step.from < static_cast<int>(vertices.size())) {
            vertices[step.from]->activate();
            vertices[step.from]->update();
        }

        if (step.from >= 0 && step.to >= 0
            && step.from < static_cast<int>(edge_matrix.size())
            && step.to < static_cast<int>(edge_matrix.size())) {
            UiEdge *edge = edge_matrix[step.from][step.to];
            if (edge) {
                if (step.from < step.to)
                    edge->activate_i_j();
                else if (step.from > step.to)
                    edge->activate_j_i();
                edge->update();
            }
        }
        return;
    }

    if (step.type == Step::VertexAdvance) {
        for (auto *vertex : vertices) {
            vertex->dis_activate();
            vertex->update();
        }

        if (step.from >= 0 && step.to >= 0
            && step.from < static_cast<int>(edge_matrix.size())
            && step.to < static_cast<int>(edge_matrix.size())) {
            UiEdge *edge = edge_matrix[step.from][step.to];
            if (edge) {
                edge->dis_activate_i_j();
                edge->dis_activate_j_i();
                edge->update();
            }
        }

        if (step.cur_v >= 0 && step.cur_v < static_cast<int>(vertices.size())) {
            vertices[step.cur_v]->set_used();
            vertices[step.cur_v]->activate();
            int value = step.cur_v + 1;
            if (step.cur_v >= 0 && step.cur_v < static_cast<int>(last_dist.size())) {
                if (last_dist[step.cur_v] >= 1000000000)
                    vertices[step.cur_v]->set_value(std::to_string(value) + "\nINF");
                else
                    vertices[step.cur_v]->set_value(std::to_string(value) + "\n" + std::to_string(last_dist[step.cur_v]));
            } else {
                vertices[step.cur_v]->set_value(std::to_string(value));
            }
            vertices[step.cur_v]->update();
        }
    }
}

void GraphWorker::dfs_reset() {
    steps.clear();
    step_index = 0;
    clear_active_edges();

    for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
        vertices[i]->dis_activate();
        vertices[i]->set_unused();
        vertices[i]->set_value(std::to_string(i + 1));
        vertices[i]->update();
    }

    for (auto *edge : edges) {
        edge->dis_activate_i_j();
        edge->dis_activate_j_i();
        edge->update();
    }
}


void GraphWorker::bfs_prepare(int start_index) {
    steps.clear();
    step_index = 0;
    last_dist.clear();
    active_edges.clear();

    int n = graph.size();
    if (n == 0) return;
    if (start_index < 0 || start_index >= n) return;

    std::vector<bool> visited(n, false);
    std::queue<int> q;

    visited[start_index] = true;
    q.push(start_index);

    Step root_step;
    root_step.type = Step::VertexAdvance;
    root_step.cur_v = start_index;
    steps.push_back(root_step);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int j = 0; j < n; j++) {
            if (graph.has_edge(v, j) && !visited[j]) {
                visited[j] = true;
                q.push(j);

                Step edge_step;
                edge_step.type = Step::EdgeActivate;
                edge_step.from = v;
                edge_step.to = j;
                steps.push_back(edge_step);

                Step vertex_step;
                vertex_step.type = Step::VertexAdvance;
                vertex_step.prev_v = v;
                vertex_step.cur_v = j;
                vertex_step.from = v;
                vertex_step.to = j;
                steps.push_back(vertex_step);
            }
        }
    }
}

void GraphWorker::dijkstra_prepare(int start_index) {
    steps.clear();
    step_index = 0;
    last_dist.clear();
    active_edges.clear();

    int n = graph.size();
    if (n == 0) return;
    if (start_index < 0 || start_index >= n) return;

    const int INF = 1000000000;
    std::vector<int> dist(n, INF);
    last_dist = dist;
    std::vector<bool> used(n, false);

    dist[start_index] = 0;

    for (int iter = 0; iter < n; iter++) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (!used[i] && (v == -1 || dist[i] < dist[v]))
                v = i;
        }
        if (v == -1 || dist[v] == INF) break;

        used[v] = true;

        Step select_step;
        select_step.type = Step::DijkstraSelect;
        select_step.cur_v = v;
        select_step.dist = dist[v];
        steps.push_back(select_step);

        for (int to = 0; to < n; to++) {
            if (!graph.has_edge(v, to)) continue;
            int *weight_ptr = graph.get_weight(v, to);
            if (!weight_ptr) continue;
            int weight = *weight_ptr;

            Step inspect_step;
            inspect_step.type = Step::DijkstraInspect;
            inspect_step.from = v;
            inspect_step.to = to;
            steps.push_back(inspect_step);

            if (dist[v] + weight < dist[to]) {
                dist[to] = dist[v] + weight;
                last_dist = dist;

                Step relax_step;
                relax_step.type = Step::DijkstraRelax;
                relax_step.from = v;
                relax_step.to = to;
                relax_step.dist = dist[to];
                steps.push_back(relax_step);
            }
        }
    }
}
