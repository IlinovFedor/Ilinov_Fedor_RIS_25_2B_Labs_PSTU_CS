#include "MainWindow.h"

MainWindow::MainWindow() : QWidget(nullptr) {
    auto *vertical_layout = new QVBoxLayout(this);

    worker = new GraphWorker(this);
    worker->draw();

    auto *input_layout = new QHBoxLayout;
    key_input = new QDoubleSpinBox(this);
    key_input->setRange(-10000.0, 10000.0);
    key_input->setDecimals(2);
    key_input->setSingleStep(1.0);

    btn_insert = new QPushButton("Insert", this);
    btn_remove = new QPushButton("Remove", this);
    btn_search = new QPushButton("Search", this);
    btn_find_min = new QPushButton("Find Min", this);

    input_layout->addWidget(new QLabel("Key:", this));
    input_layout->addWidget(key_input);
    input_layout->addWidget(btn_insert);
    input_layout->addWidget(btn_remove);
    input_layout->addWidget(btn_search);
    input_layout->addWidget(btn_find_min);
    vertical_layout->addLayout(input_layout);

    vertical_layout->addWidget(worker);

    auto *traversal_layout = new QHBoxLayout;
    btn_preorder = new QPushButton("PreOrder", this);
    btn_inorder = new QPushButton("InOrder", this);
    btn_postorder = new QPushButton("PostOrder", this);
    btn_balance = new QPushButton("Balance", this);

    traversal_layout->addWidget(btn_preorder);
    traversal_layout->addWidget(btn_inorder);
    traversal_layout->addWidget(btn_postorder);
    traversal_layout->addWidget(btn_balance);
    vertical_layout->addLayout(traversal_layout);

    auto *view_layout = new QHBoxLayout;
    btn_zoom_in = new QPushButton("Zoom In", this);
    btn_zoom_out = new QPushButton("Zoom Out", this);
    btn_reset = new QPushButton("Reset", this);
    btn_next = new QPushButton("Next Step", this);

    view_layout->addWidget(btn_zoom_in);
    view_layout->addWidget(btn_zoom_out);
    view_layout->addWidget(btn_reset);
    view_layout->addWidget(btn_next);
    vertical_layout->addLayout(view_layout);

    connect(btn_insert, &QPushButton::clicked, this, &MainWindow::on_insert_clicked);
    connect(btn_remove, &QPushButton::clicked, this, &MainWindow::on_remove_clicked);
    connect(btn_search, &QPushButton::clicked, this, &MainWindow::on_search_clicked);
    connect(btn_find_min, &QPushButton::clicked, this, &MainWindow::on_find_min_clicked);
    connect(btn_preorder, &QPushButton::clicked, this, &MainWindow::on_preorder_clicked);
    connect(btn_inorder, &QPushButton::clicked, this, &MainWindow::on_inorder_clicked);
    connect(btn_postorder, &QPushButton::clicked, this, &MainWindow::on_postorder_clicked);
    connect(btn_balance, &QPushButton::clicked, this, &MainWindow::on_balance_clicked);
    connect(btn_reset, &QPushButton::clicked, this, &MainWindow::on_reset_clicked);
    connect(btn_next, &QPushButton::clicked, this, &MainWindow::on_next_clicked);
    connect(btn_zoom_in, &QPushButton::clicked, this, &MainWindow::on_zoom_in_clicked);
    connect(btn_zoom_out, &QPushButton::clicked, this, &MainWindow::on_zoom_out_clicked);
}

void MainWindow::on_insert_clicked() {
    worker->reset();
    worker->insert_prepare(key_input->value());
}

void MainWindow::on_remove_clicked() {
    worker->reset();
    worker->remove_prepare(key_input->value());
}

void MainWindow::on_search_clicked() {
    worker->reset();
    worker->search_prepare(key_input->value());
}

void MainWindow::on_find_min_clicked() {
    worker->reset();
    worker->find_min_prepare();
}

void MainWindow::on_preorder_clicked() {
    worker->reset();
    worker->traversal_prepare(worker->tree.preOrder());
}

void MainWindow::on_inorder_clicked() {
    worker->reset();
    worker->traversal_prepare(worker->tree.inOrder());
}

void MainWindow::on_postorder_clicked() {
    worker->reset();
    worker->traversal_prepare(worker->tree.postOrder());
}

void MainWindow::on_balance_clicked() {
    worker->reset();
    worker->balance_tree();
}

void MainWindow::on_reset_clicked() {
    worker->reset();
}

void MainWindow::on_next_clicked() {
    worker->step_next();
}

void MainWindow::on_zoom_in_clicked() {
    worker->zoom_in();
}

void MainWindow::on_zoom_out_clicked() {
    worker->zoom_out();
}
