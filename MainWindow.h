#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include "Graph.h"
#include "MapCanvas.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Graph mapGraph;
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* controlPanelLayout;
    QLabel* titleLabel;
    MapCanvas* mapCanvas;

    void setupUI();
    void loadSampleData();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif
