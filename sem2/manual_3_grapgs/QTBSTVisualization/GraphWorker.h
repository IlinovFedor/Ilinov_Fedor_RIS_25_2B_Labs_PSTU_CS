#ifndef QTGRAPHVISUALIZATION_GRAPHWORKER_H
#define QTGRAPHVISUALIZATION_GRAPHWORKER_H

#include <QGraphicsView>
#include <QWidget>
#include <vector>
#include <unordered_map>
#include <functional>
#include "UiVertex.h"
#include "BST.h"

class GraphWorker : public QWidget {
    Q_OBJECT

    std::vector<UiVertex *> vertices;
    std::unordered_map<Node *, UiVertex *> node_vertex_map;
    std::vector<std::function<void()>> steps;
    int step = 0;

    QGraphicsScene *scene;
    QGraphicsView *view;

    void compute_positions(Node *node, int depth, int &index,
                           std::unordered_map<Node *, double> &x_pos,
                           std::unordered_map<Node *, double> &y_pos);
    void draw_tree();
    static std::string key_str(double key);

public:
    explicit GraphWorker(QWidget *parent);
    ~GraphWorker() override;

    BST tree;
    void draw();
    void zoom_in();
    void zoom_out();

    void insert_prepare(double key);
    void remove_prepare(double key);
    void search_prepare(double key);
    void find_min_prepare();
    void traversal_prepare(const std::vector<double> &order);
    void balance_tree();

    void step_next();
    void reset();
};

#endif
