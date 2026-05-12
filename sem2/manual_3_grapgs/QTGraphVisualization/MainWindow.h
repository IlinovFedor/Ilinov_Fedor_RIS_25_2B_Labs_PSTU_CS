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
#include "GraphWorker.h"

class MainWindow : public QWidget {
    Q_OBJECT
    QVBoxLayout *vertical_layout;
    QHBoxLayout *algorithms_layout;
    QHBoxLayout *graph_params_layout;

    QPushButton *run_bfs;
    QPushButton *run_dfs;
    QPushButton *run_dijkstra;
    QPushButton *run_floyd;

    QPushButton *edit_matrix;
    QPushButton *reset;
    QPushButton *zoom_in;
    QPushButton *zoom_out;


    GraphWorker* worker;
public:
    MainWindow();
};


#endif //QTGRAPHVISUALIZATION_MAINWINDOW_H
