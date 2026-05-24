#ifndef QTGRAPHVISUALIZATION_GRAPHWORKER_H
#define QTGRAPHVISUALIZATION_GRAPHWORKER_H

#include <QGraphicsView>
#include <QTableWidget>
#include <QLabel>
#include <QWidget>
#include <vector>
#include <functional>
#include "UiVertex.h"
#include "UiEdge.h"
#include "Graph.h"

class GraphWorker : public QWidget {
    Q_OBJECT
    std::vector<UiVertex*> vertices;
    std::vector<std::vector<UiEdge*>> edge_matrix;
    std::vector<std::function<void()>> steps;
    int step = 0;

    QGraphicsScene *scene;
    QGraphicsView *view;

    QTableWidget* table;
    QLabel* table_label;

    void draw_not_tree();
    void set_cell(int i, int j, const QString& text, const QColor& color);
    void clear_edge_highlights();

public:
    explicit GraphWorker(QWidget* parent);
    ~GraphWorker();

    Graph graph;
    void draw_graph();
    void zoom_in();
    void zoom_out();
    void bnb_prepare();
    void step_next();
    bool has_next() const { return step < static_cast<int>(steps.size()); }
    void reset();
};

#endif
