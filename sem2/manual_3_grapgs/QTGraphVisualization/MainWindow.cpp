//
// Created by localuser on 5/12/26.
//

#include "MainWindow.h"

#include "UiEdge.h"

MainWindow::MainWindow() : QWidget(nullptr){
    vertical_layout = new QVBoxLayout(this);

    Graph graph;
    graph.generateRandom(5);
    worker = new GraphWorker(this, graph);
    worker->draw_graph();

    graph_params_layout = new QHBoxLayout(this);
    edit_matrix = new QPushButton("Edit matrix", this);
    generate_random = new QPushButton("Generate random graph", this);
    generate_tree = new QPushButton("Generate tree", this);

    graph_params_layout->addWidget(edit_matrix);
    graph_params_layout->addWidget(generate_random);
    graph_params_layout->addWidget(generate_tree);
    vertical_layout->addLayout(graph_params_layout);

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

    run_layout = new QHBoxLayout(this);
    reset = new QPushButton("Reset", this);
    next = new QPushButton("Next step", this);
    run_layout->addWidget(reset);
    run_layout->addWidget(next);

    vertical_layout->addLayout(run_layout);

    zoom_in = new QPushButton("Zoom in", this);
    zoom_out = new QPushButton("Zoom out", this);

    graph_params_layout->addWidget(zoom_in);
    graph_params_layout->addWidget(zoom_out);

    connect(edit_matrix, &QPushButton::clicked, this, &MainWindow::on_edit_matrix_clicked);
    connect(generate_random, &QPushButton::clicked, this, &MainWindow::on_generate_random_clicked);
    connect(generate_tree, &QPushButton::clicked, this, &MainWindow::on_generate_tree_clicked);

    connect(zoom_in, &QPushButton::clicked, this, &MainWindow::on_zoom_in_clicked);
    connect(zoom_out, &QPushButton::clicked, this, &MainWindow::on_zoom_out_clicked);

    connect(run_dfs, &QPushButton::clicked, this, &MainWindow::on_run_dfs_clicked);
    connect(next, &QPushButton::clicked, this, &MainWindow::on_next_clicked);
    connect(reset, &QPushButton::clicked, this, &MainWindow::on_reset_clicked);
}

void MainWindow::on_edit_matrix_clicked() {
    MatrixEditor editor(worker->graph, this);
    if (editor.exec() == QDialog::Accepted) {
        worker->graph.set_matrix(editor.build_matrix());
        worker->draw_graph();
    }
}

void MainWindow::on_zoom_in_clicked() {
    worker->zoom_in();
}

void MainWindow::on_zoom_out_clicked() {
    worker->zoom_out();
}

void MainWindow::on_generate_tree_clicked() {
    worker->graph.generateTree(6, 10);
    worker->draw_graph();
}

void MainWindow::on_generate_random_clicked() {
    worker->graph.generateRandom(5, 10, 0.3);
    worker->draw_graph();
}

void MainWindow::on_run_dfs_clicked() {
    int n = worker->graph.size();
    if (n == 0) return;

    QDialog dialog(this);
    dialog.setWindowTitle("DFS start vertex");

    auto *layout = new QVBoxLayout(&dialog);
    auto *spin = new QSpinBox(&dialog);
    spin->setRange(1, n);
    spin->setValue(1);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(spin);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return;

    worker->dfs_reset();
    worker->dfs_prepare(spin->value() - 1);
}

void MainWindow::on_next_clicked() {
    worker->dfs_step_next();
}

void MainWindow::on_reset_clicked() {
    worker->dfs_reset();
}
