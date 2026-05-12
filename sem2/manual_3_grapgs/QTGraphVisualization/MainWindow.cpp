//
// Created by localuser on 5/12/26.
//

#include "MainWindow.h"

#include "UiEdge.h"

MainWindow::MainWindow() : QWidget(nullptr){
    vertical_layout = new QVBoxLayout(this);

    Graph graph;
    graph.generateTree(15);
    worker = new GraphWorker(this, graph);
    worker->draw_graph();

    vertical_layout->addWidget(worker);

    algorithms_layout = new QHBoxLayout;
    vertical_layout->addLayout(algorithms_layout);

    run_bfs = new QPushButton("BFS!", this);
    run_dfs = new QPushButton("DFS!", this);
    run_dijkstra = new QPushButton("Dijkstra!", this);
    run_floyd = new QPushButton("Floyd!", this);

    algorithms_layout->addWidget(run_bfs);
    algorithms_layout->addWidget(run_dfs);
    algorithms_layout->addWidget(run_dijkstra);
    algorithms_layout->addWidget(run_floyd);

    graph_params_layout = new QHBoxLayout;
    vertical_layout->addLayout(graph_params_layout);

    edit_matrix = new QPushButton("Edit matrix", this);
    reset = new QPushButton("Reset", this);
    zoom_in = new QPushButton("Zoom in", this);
    zoom_out = new QPushButton("Zoom out", this);


    graph_params_layout->addWidget(edit_matrix);
    graph_params_layout->addWidget(reset);
    graph_params_layout->addWidget(zoom_in);
    graph_params_layout->addWidget(zoom_out);
}
