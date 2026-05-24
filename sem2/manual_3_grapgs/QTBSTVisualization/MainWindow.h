#ifndef QTGRAPHVISUALIZATION_MAINWINDOW_H
#define QTGRAPHVISUALIZATION_MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include "GraphWorker.h"

class MainWindow : public QWidget {
    Q_OBJECT

    QDoubleSpinBox *key_input;
    QPushButton *btn_insert;
    QPushButton *btn_remove;
    QPushButton *btn_search;
    QPushButton *btn_find_min;
    QPushButton *btn_preorder;
    QPushButton *btn_inorder;
    QPushButton *btn_postorder;
    QPushButton *btn_balance;
    QPushButton *btn_reset;
    QPushButton *btn_next;
    QPushButton *btn_zoom_in;
    QPushButton *btn_zoom_out;

    GraphWorker *worker;

public:
    MainWindow();

private slots:
    void on_insert_clicked();
    void on_remove_clicked();
    void on_search_clicked();
    void on_find_min_clicked();
    void on_preorder_clicked();
    void on_inorder_clicked();
    void on_postorder_clicked();
    void on_balance_clicked();
    void on_reset_clicked();
    void on_next_clicked();
    void on_zoom_in_clicked();
    void on_zoom_out_clicked();
};

#endif
