//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_GRAPHWORKER_H
#define QTGRAPHVISUALIZATION_GRAPHWORKER_H
#include <QWidget>
#include <vector>
#include "UiVertex.h"
#include "UiEdge.h"
#include "Graph.h"

class GraphWorker : public QWidget {
    Q_OBJECT
    struct Step {
        enum Type {
            EdgeActivate,
            VertexAdvance
        } type;
        int prev_v = -1;
        int cur_v = -1;
        int from = -1;
        int to = -1;
    };

    std::vector<UiVertex*> vertices;
    std::vector<UiEdge*> edges;
    std::vector<std::vector<UiEdge*> > edge_matrix;
    std::vector<Step> steps;
    size_t step_index = 0;

    QGraphicsScene *scene;
    QGraphicsView *view;

    void draw_tree();
    void draw_not_tree();
public:
    GraphWorker(QWidget* parent, const Graph& new_graph);
    ~GraphWorker();

    Graph graph;
    void draw_graph();
    void zoom_in();
    void zoom_out();
    void dfs_prepare(int start_index);
    void dfs_step_next();
    void dfs_reset();
};


#endif //QTGRAPHVISUALIZATION_GRAPHWORKER_H
