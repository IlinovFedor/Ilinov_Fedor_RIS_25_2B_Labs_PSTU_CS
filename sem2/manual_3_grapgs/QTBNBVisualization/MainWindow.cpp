#include "MainWindow.h"

#include "UiEdge.h"
#include <chrono>
#include <thread>

MainWindow::MainWindow() : QWidget(nullptr) {
    vertical_layout = new QVBoxLayout(this);

    Graph graph;
    worker = new GraphWorker(this);
    worker->graph = graph;
    worker->draw_graph();

    graph_params_layout = new QHBoxLayout;
    edit_matrix = new QPushButton("Edit matrix", this);
    generate_random = new QPushButton("Generate random graph", this);
    generate_tree = new QPushButton("Generate tree", this);

    graph_params_layout->addWidget(edit_matrix);
    graph_params_layout->addWidget(generate_random);
    graph_params_layout->addWidget(generate_tree);
    vertical_layout->addLayout(graph_params_layout);

    vertical_layout->addWidget(worker);

    run_layout = new QHBoxLayout;
    run_bnb = new QPushButton("Run BnB", this);
    zoom_in = new QPushButton("Zoom In", this);
    zoom_out = new QPushButton("Zoom Out", this);
    reset = new QPushButton("Reset", this);
    next = new QPushButton("Next Step", this);

    run_layout->addWidget(run_bnb);
    run_layout->addWidget(zoom_in);
    run_layout->addWidget(zoom_out);
    run_layout->addWidget(reset);
    run_layout->addWidget(next);
    vertical_layout->addLayout(run_layout);

    connect(edit_matrix, &QPushButton::clicked, this, &MainWindow::on_edit_matrix_clicked);
    connect(generate_random, &QPushButton::clicked, this, &MainWindow::on_generate_random_clicked);
    connect(generate_tree, &QPushButton::clicked, this, &MainWindow::on_generate_tree_clicked);
    connect(run_bnb, &QPushButton::clicked, this, &MainWindow::on_run_bnb_clicked);
    connect(zoom_in, &QPushButton::clicked, this, &MainWindow::on_zoom_in_clicked);
    connect(zoom_out, &QPushButton::clicked, this, &MainWindow::on_zoom_out_clicked);
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

void MainWindow::on_generate_random_clicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("Vertices amount");

    auto *layout = new QVBoxLayout(&dialog);
    auto *spin = new QSpinBox(&dialog);
    spin->setRange(1, 10);
    spin->setValue(4);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(spin);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return;

    worker->graph.generateRandom(spin->value(), 10, 1.0);
    worker->draw_graph();
}

void MainWindow::on_generate_tree_clicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("Vertices amount");

    auto *layout = new QVBoxLayout(&dialog);
    auto *spin = new QSpinBox(&dialog);
    spin->setRange(1, 10);
    spin->setValue(4);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(spin);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return;

    worker->graph.generateTree(spin->value(), 10);
    worker->draw_graph();
}

void MainWindow::on_run_bnb_clicked() {
    int n = worker->graph.size();
    if (n == 0) return;

    worker->reset();
    worker->bnb_prepare();
}

void MainWindow::on_reset_clicked() {
    worker->reset();
}

void MainWindow::on_next_clicked() {
    if (anim_timer && anim_timer->isActive()) return;
    if (!worker->has_next()) return;
    if (!anim_timer) {
        anim_timer = new QTimer(this);
        connect(anim_timer, &QTimer::timeout, this, [this]() {
            worker->step_next();
            if (!worker->has_next())
                anim_timer->stop();
        });
    }
    anim_timer->start(0);
}

void MainWindow::on_zoom_in_clicked() {
    worker->zoom_in();
}

void MainWindow::on_zoom_out_clicked() {
    worker->zoom_out();
}
