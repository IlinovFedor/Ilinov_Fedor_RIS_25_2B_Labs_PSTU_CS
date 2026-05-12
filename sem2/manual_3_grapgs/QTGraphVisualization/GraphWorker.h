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
    std::vector<UiVertex*> vertices;
    std::vector<UiEdge*> edges;

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
};


#endif //QTGRAPHVISUALIZATION_GRAPHWORKER_H
