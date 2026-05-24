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

        for (int c: children[v])
            assign_tree_positions(c, depth + 1, children, x_pos, y_pos, leaf_counter, h_step, v_step);

        x_pos[v] = (x_pos[children[v].front()] + x_pos[children[v].back()]) / 2.0;
    }
}

void GraphWorker::clear_active_edges() {
    for (auto *edge: active_edges) {
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
    edge_matrix.clear();

    int n = graph.size();
    if (n == 0) return;

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

    std::vector<std::vector<int> > children(n);
    std::vector<bool> used(n, false);
    std::queue<int> q;
    q.push(root);
    used[root] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next = 0; next < n; next++) {
            if (!used[next] && graph.has_edge(cur, next)) {
                used[next] = true;
                children[cur].push_back(next);
                q.push(next);
            }
        }
    }

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

    for (int i = 0; i < n; i++) {
        auto *v = new UiVertex(std::to_string(i + 1));
        v->set_pos(x_pos[i] + shift_x, y_pos[i] + shift_y);
        vertices.push_back(v);
    }

    edge_matrix.assign(n, std::vector<UiEdge *>(n, nullptr));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph.has_edge(i, j) || graph.has_edge(j, i)) {
                auto *e = new UiEdge(vertices[i], vertices[j]);
                if (graph.has_edge(i, j)) {
                    e->set_i_j_weight(graph.get_weight(i, j));
                    edge_matrix[i][j] = e;
                }
                if (graph.has_edge(j, i)) {
                    e->set_j_i_weight(graph.get_weight(j, i));
                    edge_matrix[j][i] = e;
                }
            }
        }
    }

    for (auto v: edge_matrix)
        for (auto ui_edge: v)
            if (ui_edge != nullptr)
                scene->addItem(ui_edge);
    for (auto vertex: vertices) scene->addItem(vertex);
}

void GraphWorker::draw_not_tree() {
    scene->clear();
    vertices.clear();
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

    edge_matrix.assign(n, std::vector<UiEdge *>(n, nullptr));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph.has_edge(i, j) || graph.has_edge(j, i)) {
                auto *e = new UiEdge(vertices[i], vertices[j]);
                if (graph.has_edge(i, j)) {
                    e->set_i_j_weight(graph.get_weight(i, j));
                    edge_matrix[i][j] = e;
                }
                if (graph.has_edge(j, i)) {
                    e->set_j_i_weight(graph.get_weight(j, i));
                    edge_matrix[j][i] = e;
                }
            }
        }
    }

    for (auto v: edge_matrix)
        for (auto ui_edge: v)
            if (ui_edge != nullptr)
                scene->addItem(ui_edge);
    for (auto vertex: vertices) scene->addItem(vertex);
}

GraphWorker::GraphWorker(QWidget *parent, const Graph &new_graph) : QWidget(parent) {
    table = new QTableWidget(this);
    table->hide();
    table->setMaximumHeight(200);
    table_label = new QLabel(this);
    table_label->hide();

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    graph = new_graph;

    view->setRenderHint(QPainter::Antialiasing);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setInteractive(true);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    layout->addWidget(table_label);
    layout->addWidget(table);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GraphWorker::~GraphWorker() {
    for (auto *v: vertices) delete v;
    for (auto v: edge_matrix)
        for (auto ui_edge: v)
            if (ui_edge != nullptr)
                delete ui_edge;
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
    step = 0;
    int n = graph.size();

    std::vector<bool> used(n, false);
    std::function<void(int, int)> dfs = [&](int node, int prev) {
        used[node] = true;

        steps.push_back([this, node, prev]() {
            vertices[prev]->make_blue();
            vertices[node]->make_red();
            auto edge = edge_matrix[prev][node];
            if (edge) {
                if (node < prev)
                    edge->dis_activate_j_i();
                else if (node > prev)
                    edge->dis_activate_i_j();
            }
        });


        for (int j = 0; j < n; j++) {
            if (graph.has_edge(node, j) && !used[j]) {
                steps.push_back([this, node, j]() {
                    UiEdge *edge = edge_matrix[node][j];
                    if (node < j)
                        edge->activate_i_j();
                    else
                        edge->activate_j_i();
                });

                dfs(j, node);

                steps.push_back([this, node, j]() {
                    vertices[node]->make_red();
                    vertices[j]->make_blue();
                });
            }
        }
    };

    dfs(start_index, start_index);
}

void GraphWorker::step_next() {
    if (step >= static_cast<int>(steps.size())) return;
    steps[step]();
    step++;
    qDebug() << step;
}

void GraphWorker::reset() {
    steps.clear();
    step = 0;
    clear_active_edges();

    for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
        vertices[i]->make_black();
        vertices[i]->set_value(std::to_string(i + 1));
        vertices[i]->update();
    }
    for (auto v: edge_matrix)
        for (auto ui_edge: v)
            if (ui_edge != nullptr) {
                ui_edge->dis_activate_i_j();
                ui_edge->dis_activate_j_i();
                ui_edge->update();
            }
    table->hide();
    table_label->hide();
}

void GraphWorker::bfs_prepare(int start_index) {
    steps.clear();
    step = 0;
    int n = graph.size();
    std::vector<bool> used(n, false);
    std::queue<int> q;

    used[start_index] = true;
    q.push(start_index);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int j = 0; j < n; j++) {
            if (graph.has_edge(node, j) && !used[j]) {
                used[j] = true;
                q.push(j);
                steps.push_back([this, node]() {
                    vertices[node]->make_red();
                });
                steps.push_back([this, node, j]() {
                    auto edge = edge_matrix[node][j];
                    if (edge)
                        node < j ? edge->activate_i_j() : edge->activate_j_i();
                });

                steps.push_back([this, node, j]() {
                    vertices[node]->make_blue();
                    auto edge = edge_matrix[node][j];
                    if (edge)
                        node < j ? edge->dis_activate_i_j() : edge->dis_activate_j_i();
                    vertices[j]->make_red();
                });
                steps.push_back([this, j]() {
                    vertices[j]->make_blue();
                });
            }
        }
    }
}


void GraphWorker::dijkstra_prepare(int start_index) {
    steps.clear();
    step = 0;
    int n = graph.size();
    std::vector<bool> used(n, false);
    std::vector<int> d(n, INT_MAX);
    d[start_index] = 0;

    for (int i = 0; i < n; i++)
        vertices[i]->set_value(std::to_string(i + 1) + "\n+inf");
    vertices[start_index]->set_value(std::to_string(start_index + 1) + "\n0");

    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (v == -1 || d[v] == INT_MAX) break;
        used[v] = true;

        steps.push_back([this, v]() {
            vertices[v]->make_red();
        });

        for (int e = 0; e < n; e++) {
            auto weight = graph.get_matrix()[v][e];
            if (weight == nullptr) continue;
            if (d[v] + *weight >= d[e]) continue;

            d[e] = d[v] + *weight;
            int new_dist = d[e];
            std::string new_val = std::to_string(e + 1) + "\n" + std::to_string(new_dist);

            steps.push_back([this, v, e, new_val]() {
                auto *edge = edge_matrix[v][e];
                if (edge)
                    v < e ? edge->activate_i_j() : edge->activate_j_i();
                vertices[e]->make_green();
                vertices[e]->set_value(new_val);
            });

            steps.push_back([this, v, e]() {
                auto *edge = edge_matrix[v][e];
                if (edge)
                    v < e ? edge->dis_activate_i_j() : edge->dis_activate_j_i();
                vertices[e]->make_black();
            });
        }

        steps.push_back([this, v]() {
            vertices[v]->make_blue();
        });
    }
}

void GraphWorker::set_cell(int i, int j, const QString& text, const QColor& color) {
    auto* item = table->item(i, j);
    if (!item) {
        item = new QTableWidgetItem();
        table->setItem(i, j, item);
    }
    item->setText(text);
    item->setBackground(color);
    item->setTextAlignment(Qt::AlignCenter);
}

void GraphWorker::floyd_prepare() {
    steps.clear();
    step = 0;
    int n = graph.size();

    table->show();
    table_label->show();
    table->setRowCount(n);
    table->setColumnCount(n);

    for (int i = 0; i < n; i++) {
        table->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i + 1)));
        table->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i + 1)));
        table->setColumnWidth(i, 50);
        table->setRowHeight(i, 30);
    }

    std::vector<std::vector<int>> d(n, std::vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph.get_matrix()[i][j] != nullptr)
                d[i][j] = *graph.get_matrix()[i][j];

    table_label->setText("Initial stage");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            QString val = d[i][j] == INT_MAX ? "+inf" : QString::number(d[i][j]);
            set_cell(i, j, val, Qt::white);
        }

    for (int k = 0; k < n; k++) {
        steps.push_back([this, k, d, n]() {
            table_label->setText(QString("Throw: %1").arg(k + 1));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    QString val = d[i][j] == INT_MAX ? "+inf" : QString::number(d[i][j]);
                    QColor color = (i == k || j == k) ? QColor(200, 200, 255) : Qt::white;
                    set_cell(i, j, val, color);
                }
            for (auto* v : vertices) v->make_black();
            vertices[k]->make_blue();
        });

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] == INT_MAX || d[k][j] == INT_MAX) continue;
                if (d[i][k] + d[k][j] >= d[i][j]) continue;

                d[i][j] = d[i][k] + d[k][j];
                int new_dist = d[i][j];

                steps.push_back([this, i, j, k, d, n, new_dist]() {
                    table_label->setText(QString("d[%1][%2] throw %3 = %4")
                        .arg(i+1).arg(j+1).arg(k+1).arg(new_dist));

                    for (int a = 0; a < n; a++)
                        for (int b = 0; b < n; b++) {
                            QString val = d[a][b] == INT_MAX ? "+inf" : QString::number(d[a][b]);
                            QColor color = (a == k || b == k) ? QColor(200, 200, 255) : Qt::white;
                            set_cell(a, b, val, color);
                        }

                    for (int b = 0; b < n; b++)
                        table->item(i, b)->setBackground(QColor(255, 180, 180));
                    for (int a = 0; a < n; a++)
                        table->item(a, j)->setBackground(QColor(255, 255, 180));
                    for (int a = 0; a < n; a++) {
                        table->item(a, k)->setBackground(QColor(200, 200, 255));
                        table->item(k, a)->setBackground(QColor(200, 200, 255));
                    }
                    set_cell(i, j, QString::number(new_dist), QColor(180, 255, 180));

                    for (auto* v : vertices) v->make_black();
                    vertices[k]->make_blue();
                    vertices[i]->make_red();
                    vertices[j]->make_green();
                });
            }
        }
    }

    steps.push_back([this, d, n]() {
        table_label->setText("The end");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                QString val = d[i][j] == INT_MAX ? "+inf" : QString::number(d[i][j]);
                set_cell(i, j, val, QColor(220, 255, 220));
            }
        for (auto* v : vertices) v->make_black();
    });
}