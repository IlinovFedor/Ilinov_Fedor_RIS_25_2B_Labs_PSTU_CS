//
// Created by localuser on 5/13/26.
//

#include "MatrixEditor.h"

#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>

MatrixEditor::MatrixEditor(const Graph &graph, QWidget *parent)
    : QDialog(parent), graph(graph) {
    setWindowTitle("Edit matrix");

    table = new QTableWidget(this);
    table->setEditTriggers(QAbstractItemView::DoubleClicked
                           | QAbstractItemView::SelectedClicked
                           | QAbstractItemView::EditKeyPressed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    add_vertex = new QPushButton("Add vertex", this);
    remove_vertex = new QPushButton("Remove vertex", this);
    buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(add_vertex);
    buttons_layout->addWidget(remove_vertex);
    buttons_layout->addWidget(buttons);

    auto *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(table);
    main_layout->addLayout(buttons_layout);
    setLayout(main_layout);

    load_from_graph();

    connect(add_vertex, &QPushButton::clicked, this, &MatrixEditor::add_vertex_row_col);
    connect(remove_vertex, &QPushButton::clicked, this, &MatrixEditor::remove_vertex_row_col);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void MatrixEditor::load_from_graph() {
    const auto &matrix = graph.get_matrix();
    int n = matrix.size();

    table->setRowCount(n);
    table->setColumnCount(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == nullptr) {
                table->setItem(i, j, new QTableWidgetItem(""));
            } else {
                table->setItem(i, j, new QTableWidgetItem(QString::number(*matrix[i][j])));
            }
        }
    }
}

std::vector<std::vector<int *> > MatrixEditor::build_matrix_from_table() const {
    int n = table->rowCount();
    std::vector<std::vector<int *> > matrix(n, std::vector<int *>(n, nullptr));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (!item) continue;
            QString text = item->text().trimmed();
            if (text.isEmpty()) continue;
            bool ok = false;
            int value = text.toInt(&ok);
            if (!ok) continue;
            matrix[i][j] = new int(value);
        }
    }

    return matrix;
}

void MatrixEditor::add_vertex_row_col() {
    int n = table->rowCount();
    table->setRowCount(n + 1);
    table->setColumnCount(n + 1);

    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (table->item(i, j)) continue;
            table->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}

void MatrixEditor::remove_vertex_row_col() {
    int n = table->rowCount();
    table->setRowCount(n - 1);
    table->setColumnCount(n - 1);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (table->item(i, j)) continue;
            table->setItem(i, j, new QTableWidgetItem(""));
        }
    }
}

std::vector<std::vector<int *> > MatrixEditor::build_matrix() const {
    return build_matrix_from_table();
}
