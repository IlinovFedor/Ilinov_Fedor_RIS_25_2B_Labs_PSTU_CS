//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_GRAPHWORKER_H
#define QTGRAPHVISUALIZATION_GRAPHWORKER_H
#include <QGraphicsView>
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
            VertexAdvance,
            DijkstraSelect,
            DijkstraInspect,
            DijkstraRelax
        } type;
        int prev_v = -1;
        int cur_v = -1;
        int from = -1;
        int to = -1;
        int dist = -1;
    };

    std::vector<UiVertex*> vertices;
    std::vector<UiEdge*> edges;
    std::vector<std::vector<UiEdge*> > edge_matrix;
    std::vector<Step> steps;
    size_t step_index = 0;
    std::vector<int> last_dist;
    std::vector<UiEdge*> active_edges;

    QGraphicsScene *scene;
    QGraphicsView *view;

    void draw_tree();
    void draw_not_tree();
    void clear_active_edges();
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
};


#endif //QTGRAPHVISUALIZATION_GRAPHWORKER_H
