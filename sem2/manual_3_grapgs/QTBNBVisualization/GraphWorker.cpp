#include "GraphWorker.h"

#include <QGraphicsView>
#include <QVBoxLayout>
#include <cmath>
#include <queue>
#include <algorithm>
#include <climits>

static const int BNB_INF = 1e9;

GraphWorker::GraphWorker(QWidget *parent) : QWidget(parent) {
    table = new QTableWidget(this);
    table->hide();
    table->setMaximumHeight(200);
    table_label = new QLabel(this);
    table_label->hide();

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
    layout->addWidget(table_label);
    layout->addWidget(table);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GraphWorker::~GraphWorker() {
    for (auto *v : vertices) delete v;
    for (auto v : edge_matrix)
        for (auto e : v)
            if (e) delete e;
}

void GraphWorker::draw_not_tree() {
    scene->clear();
    vertices.clear();
    edge_matrix.clear();

    int n = graph.size();
    if (n == 0) return;

    const double radius_val = 500.0;
    const double step_angle = 2.0 * M_PI / n;
    QPointF center = view->mapToScene(view->viewport()->rect().center());

    for (int i = 0; i < n; i++) {
        double angle = step_angle * i;
        double x = center.x() + radius_val * std::cos(angle);
        double y = center.y() + radius_val * std::sin(angle);
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

    for (auto v : edge_matrix)
        for (auto ui_edge : v)
            if (ui_edge)
                scene->addItem(ui_edge);
    for (auto v : vertices)
        scene->addItem(v);
}

void GraphWorker::draw_graph() {
    draw_not_tree();
}

void GraphWorker::zoom_in() {
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    view->scale(1.2, 1.2);
}

void GraphWorker::zoom_out() {
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    view->scale(1.0 / 1.2, 1.0 / 1.2);
}

void GraphWorker::set_cell(int i, int j, const QString &text, const QColor &color) {
    auto *item = table->item(i, j);
    if (!item) {
        item = new QTableWidgetItem();
        table->setItem(i, j, item);
    }
    item->setText(text);
    item->setBackground(color);
    item->setTextAlignment(Qt::AlignCenter);
}

void GraphWorker::clear_edge_highlights() {
    for (auto v : edge_matrix)
        for (auto e : v)
            if (e) {
                e->reset_colors();
                e->update();
            }
}

void GraphWorker::step_next() {
    if (step >= static_cast<int>(steps.size())) return;
    steps[step]();
    step++;
}

void GraphWorker::reset() {
    steps.clear();
    step = 0;
    clear_edge_highlights();
    for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
        vertices[i]->make_black();
        vertices[i]->set_value(std::to_string(i + 1));
        vertices[i]->update();
    }
    for (auto v : edge_matrix)
        for (auto e : v)
            if (e) {
                e->dis_activate_i_j();
                e->dis_activate_j_i();
                e->update();
            }
    table->hide();
    table_label->hide();
}

void GraphWorker::bnb_prepare() {
    steps.clear();
    step = 0;

    int n = graph.size();
    if (n == 0) return;

    // Build cost matrix from graph
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, BNB_INF));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && graph.has_edge(i, j))
                mat[i][j] = *graph.get_weight(i, j);

    // Setup table
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

    // Helper: convert working m×m matrix to full n×n display matrix
    auto build_full = [n](const std::vector<std::vector<int>> &small,
                           const std::vector<int> &rows,
                           const std::vector<int> &cols) {
        std::vector<std::vector<int>> full(n, std::vector<int>(n, BNB_INF));
        for (size_t i = 0; i < small.size() && i < rows.size(); i++)
            for (size_t j = 0; j < small[i].size() && j < cols.size(); j++)
                if (rows[i] < n && cols[j] < n)
                    full[rows[i]][cols[j]] = small[i][j];
        return full;
    };

    // Helper: push a visualization step
    auto push_step = [this, n](const std::vector<std::vector<int>> &matrix,
                                int bound, int best,
                                const std::vector<std::pair<int, int>> &included,
                                const std::vector<std::pair<int, int>> &excluded,
                                int branch_i, int branch_j,
                                const std::string &msg) {
        steps.push_back([this, n, matrix, bound, best, included, excluded, branch_i, branch_j, msg]() {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    QString val;
                    QColor bg = Qt::white;
                    if (matrix[i][j] >= BNB_INF / 2)
                        val = "inf";
                    else
                        val = QString::number(matrix[i][j]);
                    set_cell(i, j, val, bg);
                }

            QString label = QString::fromStdString(msg);
            if (bound < BNB_INF / 2)
                label += QString("  LB: %1").arg(bound);
            if (best < BNB_INF / 2)
                label += QString("  Best: %1").arg(best);
            table_label->setText(label);

            clear_edge_highlights();
            auto color_arrow = [](UiEdge *e, int from, int to, UiEdge::DirColor c) {
                if (from < to) e->set_i_j_color(c);
                else           e->set_j_i_color(c);
            };
            for (auto &p : included)
                if (edge_matrix[p.first][p.second])
                    color_arrow(edge_matrix[p.first][p.second], p.first, p.second,
                                UiEdge::DirColor::Included);
            for (auto &p : excluded)
                if (edge_matrix[p.first][p.second])
                    color_arrow(edge_matrix[p.first][p.second], p.first, p.second,
                                UiEdge::DirColor::Excluded);
            if (branch_i >= 0 && branch_j >= 0 && edge_matrix[branch_i][branch_j])
                color_arrow(edge_matrix[branch_i][branch_j], branch_i, branch_j,
                            UiEdge::DirColor::Current);
        });
    };

    // Initial best = INF, best_path empty
    int best = BNB_INF;
    std::vector<std::pair<int, int>> best_path;

    push_step(mat, 0, best, {}, {}, -1, -1, "Initial matrix");

    // Recursive BnB (Little's algorithm)
    std::function<void(std::vector<std::vector<int>>, int,
                       std::vector<std::pair<int, int>>,
                       std::vector<std::pair<int, int>>,
                       std::vector<int>, std::vector<int>)>
        bnb_rec;

    bnb_rec = [&](std::vector<std::vector<int>> cmat, int bound,
                  std::vector<std::pair<int, int>> included,
                  std::vector<std::pair<int, int>> excluded,
                  std::vector<int> row_cities,
                  std::vector<int> col_cities) {
        int m = cmat.size();

        // Reduce rows
        for (int i = 0; i < m; i++) {
            int row_min = BNB_INF;
            for (int j = 0; j < m; j++)
                if (cmat[i][j] < row_min) row_min = cmat[i][j];
            if (row_min >= BNB_INF / 2) return; // impossible
            if (row_min > 0) {
                for (int j = 0; j < m; j++)
                    if (cmat[i][j] < BNB_INF / 2)
                        cmat[i][j] -= row_min;
                bound += row_min;
                push_step(build_full(cmat, row_cities, col_cities), bound, best,
                          included, excluded, -1, -1,
                          "Row reduce city " + std::to_string(row_cities[i] + 1) +
                              ", sub " + std::to_string(row_min));
            }
        }

        // Reduce columns
        for (int j = 0; j < m; j++) {
            int col_min = BNB_INF;
            for (int i = 0; i < m; i++)
                if (cmat[i][j] < col_min) col_min = cmat[i][j];
            if (col_min >= BNB_INF / 2) return;
            if (col_min > 0) {
                for (int i = 0; i < m; i++)
                    if (cmat[i][j] < BNB_INF / 2)
                        cmat[i][j] -= col_min;
                bound += col_min;
                push_step(build_full(cmat, row_cities, col_cities), bound, best,
                          included, excluded, -1, -1,
                          "Column reduce city " + std::to_string(col_cities[j] + 1) +
                              ", sub " + std::to_string(col_min));
            }
        }

        // Prune
        if (bound >= best) {
            push_step(build_full(cmat, row_cities, col_cities), bound, best,
                      included, excluded, -1, -1, "Prune (bound >= best)");
            return;
        }

        // Base case: 2x2 matrix → complete tour (try all 2 matchings)
        if (m == 2) {
            static const int matchings[2][2][2] = {{{0,1},{1,0}}, {{0,0},{1,1}}};
            bool found_tour = false;
            for (auto &matching : matchings) {
                int u = matching[0][0], v = matching[0][1];
                int x = matching[1][0], y = matching[1][1];
                if (cmat[u][v] < BNB_INF / 2 && cmat[x][y] < BNB_INF / 2) {
                    auto tour = included;
                    tour.emplace_back(row_cities[u], col_cities[v]);
                    tour.emplace_back(row_cities[x], col_cities[y]);
                    if (bound < best) {
                        best = bound;
                        best_path = tour;
                    }
                    push_step(build_full(cmat, row_cities, col_cities), bound, best,
                              tour, excluded, -1, -1, "Tour found!");
                    found_tour = true;
                }
            }
            if (!found_tour) {
                push_step(build_full(cmat, row_cities, col_cities), bound, best,
                          included, excluded, -1, -1,
                          "Cannot complete tour (edge missing)");
            }
            return;
        }

        // Find branching edge (max penalty zero)
        int best_i = -1, best_j = -1, max_penalty = -1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (cmat[i][j] != 0) continue;
                int row_min = BNB_INF;
                for (int k = 0; k < m; k++)
                    if (k != j && cmat[i][k] < row_min) row_min = cmat[i][k];
                int col_min = BNB_INF;
                for (int k = 0; k < m; k++)
                    if (k != i && cmat[k][j] < col_min) col_min = cmat[k][j];
                int penalty = (row_min < BNB_INF / 2 ? row_min : 0) +
                              (col_min < BNB_INF / 2 ? col_min : 0);
                if (penalty > max_penalty) {
                    max_penalty = penalty;
                    best_i = i;
                    best_j = j;
                }
            }
        }

        if (best_i < 0 || best_j < 0) return; // no zero

        int orig_i = row_cities[best_i];
        int orig_j = col_cities[best_j];

        push_step(build_full(cmat, row_cities, col_cities), bound, best,
                  included, excluded, orig_i, orig_j,
                  "Branch on (" + std::to_string(orig_i + 1) + "," +
                      std::to_string(orig_j + 1) + ") penalty=" +
                      std::to_string(max_penalty));

        // Exclude branch: forbid edge (orig_i, orig_j)
        {
            auto exc_mat = cmat;
            exc_mat[best_i][best_j] = BNB_INF;
            auto exc_exc = excluded;
            exc_exc.emplace_back(orig_i, orig_j);
            push_step(build_full(exc_mat, row_cities, col_cities), bound, best,
                      included, exc_exc, orig_i, orig_j,
                      "Exclude (" + std::to_string(orig_i + 1) + "," +
                          std::to_string(orig_j + 1) + ")");
            bnb_rec(exc_mat, bound, included, exc_exc, row_cities, col_cities);
        }

        // Include branch: add edge, remove row/col, forbid reverse
        {
            // Correct reverse edge: from orig_j to orig_i
            int rev_i = -1, rev_j = -1;
            for (int k = 0; k < m; k++) {
                if (row_cities[k] == orig_j) rev_i = k;
                if (col_cities[k] == orig_i) rev_j = k;
            }
            if (rev_i >= 0 && rev_j >= 0)
                cmat[rev_i][rev_j] = BNB_INF;

            std::vector<std::vector<int>> inc_mat(m - 1, std::vector<int>(m - 1));
            std::vector<int> new_rows, new_cols;

            for (int i = 0; i < m; i++) {
                if (i == best_i) continue;
                new_rows.push_back(row_cities[i]);
                int ri = (i > best_i) ? i - 1 : i;
                for (int j = 0; j < m; j++) {
                    if (j == best_j) continue;
                    inc_mat[ri][(j > best_j) ? j - 1 : j] = cmat[i][j];
                }
            }
            for (int j = 0; j < m; j++)
                if (j != best_j) new_cols.push_back(col_cities[j]);

            auto inc_inc = included;
            inc_inc.emplace_back(orig_i, orig_j);

            // Subtour prevention: forbid edge (tail, head)
            int sub_tail = orig_j;
            for (bool cont = true; cont;) {
                cont = false;
                for (auto &e : inc_inc)
                    if (e.first == sub_tail) { sub_tail = e.second; cont = true; break; }
            }
            int sub_head = orig_i;
            for (bool cont = true; cont;) {
                cont = false;
                for (auto &e : inc_inc)
                    if (e.second == sub_head) { sub_head = e.first; cont = true; break; }
            }
            if (!(sub_tail == orig_j && sub_head == orig_i)) {
                int fi = -1, fj = -1;
                for (int k = 0; k < m - 1; k++) {
                    if (new_rows[k] == sub_tail) fi = k;
                    if (new_cols[k] == sub_head) fj = k;
                }
                if (fi >= 0 && fj >= 0)
                    inc_mat[fi][fj] = BNB_INF;
            }

            push_step(build_full(inc_mat, new_rows, new_cols), bound, best,
                      inc_inc, excluded, orig_i, orig_j,
                      "Include (" + std::to_string(orig_i + 1) + "," +
                          std::to_string(orig_j + 1) + ")");
            bnb_rec(inc_mat, bound, inc_inc, excluded, new_rows, new_cols);
        }
    };

    std::vector<int> init_cities(n);
    for (int i = 0; i < n; i++) init_cities[i] = i;

    bnb_rec(mat, 0, {}, {}, init_cities, init_cities);

    if (best < BNB_INF / 2) {
        push_step(mat, best, best, best_path, {}, -1, -1,
                  "Optimal tour length: " + std::to_string(best));
    } else {
        push_step(mat, 0, BNB_INF, {}, {}, -1, -1, "No tour exists");
    }
}
