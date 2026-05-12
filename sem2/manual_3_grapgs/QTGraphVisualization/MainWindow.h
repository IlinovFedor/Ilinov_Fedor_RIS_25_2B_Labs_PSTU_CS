//
// Created by localuser on 5/12/26.
//

#ifndef QTGRAPHVISUALIZATION_MAINWINDOW_H
#define QTGRAPHVISUALIZATION_MAINWINDOW_H
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCheckBox>
#include <QPushButton>
#include <QDialog>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "GraphWorker.h"
#include "MatrixEditor.h"

class MainWindow : public QWidget {
    Q_OBJECT
    QVBoxLayout *vertical_layout;
    QHBoxLayout *algorithms_layout;
    QHBoxLayout *graph_params_layout;
    QHBoxLayout *view_params_layout;
    QHBoxLayout *run_layout;

    QPushButton *run_bfs;
    QPushButton *run_dfs;
    QPushButton *run_dijkstra;
    QPushButton *run_floyd;

    QPushButton *edit_matrix;
    QPushButton *generate_tree;
    QPushButton *generate_random;

    QPushButton *reset;
    QPushButton *next;

    QPushButton *zoom_in;
    QPushButton *zoom_out;


    GraphWorker* worker;
public:
    MainWindow();

private slots:
    void on_edit_matrix_clicked();
    void on_zoom_in_clicked();
    void on_zoom_out_clicked();
    void on_generate_tree_clicked();
    void on_generate_random_clicked();
    void on_run_dfs_clicked();
    void on_run_bfs_clicked();
    void on_run_dijkstra_clicked();
    void on_next_clicked();
    void on_reset_clicked();
};


#endif //QTGRAPHVISUALIZATION_MAINWINDOW_H
