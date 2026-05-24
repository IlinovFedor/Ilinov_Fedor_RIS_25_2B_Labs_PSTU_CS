//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_GRAPH_H
#define QTGRAPHVISUALIZATION_GRAPH_H
#include <cstdlib>
#include <queue>
#include <vector>

class Graph {
    std::vector<std::vector<int *> > matrix;

public:
    Graph() = default;
    Graph(const Graph &other);
    ~Graph();
    Graph &operator=(const Graph &other);
    void clear_matrix();
    const std::vector<std::vector<int *> > &get_matrix() const;
    void set_matrix(const std::vector<std::vector<int *> > &new_matrix);

    bool is_visual_tree();

    void generateRandom(int n, int maxWeight = 10, double edgeProbability = 0.5);
    void generateTree(int n, int maxWeight = 10);

    int size();
    bool has_edge(int i, int j);
    int *get_weight(int i, int j);

    void dfs(uint n, std::vector<bool>& visited);
};


#endif //QTGRAPHVISUALIZATION_GRAPH_H
