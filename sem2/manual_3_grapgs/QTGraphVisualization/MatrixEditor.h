//
// Created by localuser on 5/13/26.
//

#ifndef QTGRAPHVISUALIZATION_MATRIXEDITOR_H
#define QTGRAPHVISUALIZATION_MATRIXEDITOR_H

#include <QDialog>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include "Graph.h"

class MatrixEditor : public QDialog {
    Q_OBJECT

    const Graph &graph;
    QTableWidget *table;
    QPushButton *add_vertex;
    QPushButton *remove_vertex;
    QDialogButtonBox *buttons;

    void load_from_graph();
    void add_vertex_row_col();
    void remove_vertex_row_col();
    std::vector<std::vector<int *> > build_matrix_from_table() const;

public:
    MatrixEditor(const Graph &graph, QWidget *parent = nullptr);
    std::vector<std::vector<int *> > build_matrix() const;
};

#endif //QTGRAPHVISUALIZATION_MATRIXEDITOR_H
