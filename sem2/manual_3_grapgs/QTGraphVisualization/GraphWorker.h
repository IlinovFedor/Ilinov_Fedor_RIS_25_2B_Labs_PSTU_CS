//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_GRAPHWORKER_H
#define QTGRAPHVISUALIZATION_GRAPHWORKER_H
#include <QGraphicsView>
#include <QTableWidget>
#include <QLabel>
#include <QWidget>
#include <vector>
#include "UiVertex.h"
#include "UiEdge.h"
#include "Graph.h"

class GraphWorker : public QWidget {
    Q_OBJECT
    std::vector<UiVertex*> vertices;
    std::vector<std::vector<UiEdge*> > edge_matrix;
    std::vector<std::function<void()>> steps;
    int step = 0;
    std::vector<int> last_dist;
    std::vector<UiEdge*> active_edges;

    QGraphicsScene *scene;
    QGraphicsView *view;

    QTableWidget* table;
    QLabel* table_label;

    void draw_tree();
    void draw_not_tree();
    void clear_active_edges();
    void set_cell(int i, int j, const QString& text, const QColor& color);
public:
    GraphWorker(QWidget* parent, const Graph& new_graph);
    ~GraphWorker();

    Graph graph;
    void draw_graph();
    void zoom_in();
    void zoom_out();
    void dfs_prepare(int start_index);
    void step_next();
    void reset();
    void bfs_prepare(int start_index);
    void dijkstra_prepare(int start_index);

    void floyd_prepare();
};


#endif //QTGRAPHVISUALIZATION_GRAPHWORKER_H
