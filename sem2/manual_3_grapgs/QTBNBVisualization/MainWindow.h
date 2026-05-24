#ifndef QTGRAPHVISUALIZATION_MAINWINDOW_H
#define QTGRAPHVISUALIZATION_MAINWINDOW_H

#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QDialog>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QTimer>
#include "GraphWorker.h"
#include "MatrixEditor.h"

class MainWindow : public QWidget {
    Q_OBJECT
    QVBoxLayout *vertical_layout;
    QHBoxLayout *graph_params_layout;
    QHBoxLayout *run_layout;

    QPushButton *edit_matrix;
    QPushButton *generate_random;
    QPushButton *generate_tree;

    QPushButton *run_bnb;
    QPushButton *reset;
    QPushButton *next;
    QPushButton *zoom_in;
    QPushButton *zoom_out;

    GraphWorker *worker;
    QTimer *anim_timer = nullptr;

public:
    MainWindow();

private slots:
    void on_edit_matrix_clicked();
    void on_generate_random_clicked();
    void on_generate_tree_clicked();
    void on_run_bnb_clicked();
    void on_reset_clicked();
    void on_next_clicked();
    void on_zoom_in_clicked();
    void on_zoom_out_clicked();
};

#endif
