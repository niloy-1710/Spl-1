#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mapCanvas(nullptr) {
    setWindowTitle("Map Navigation System - SPL 1 (IIT DU)");
    resize(1200, 750);

    loadSampleData();
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    // Visual Map Canvas
    mapCanvas = new MapCanvas(this);
    mapCanvas->setGraph(&mapGraph);
    mainLayout->addWidget(mapCanvas, 4); // 80% width

    // Control panel sidebar
    controlPanelLayout = new QVBoxLayout();
    titleLabel = new QLabel("<h2>Map Navigation</h2><p><b>Dhaka University Campus</b></p>", this);
    controlPanelLayout->addWidget(titleLabel);

    controlPanelLayout->addStretch();
    mainLayout->addLayout(controlPanelLayout, 1); // 20% width

    statusBar()->showMessage(QString("System Ready | %1 Locations Loaded").arg(mapGraph.getLocationCount()));
}

void MainWindow::loadSampleData() {
    if (!mapGraph.loadFile("map.txt")) {
        // Fallback default landmarks
        mapGraph.addLocation("IIT", 250, 300);
        mapGraph.addLocation("Curzon", 380, 200);
        mapGraph.addLocation("TSC", 150, 120);
        mapGraph.addLocation("Central_Library", 200, 180);
        mapGraph.addLocation("Shaheed_Minar", 300, 260);

        mapGraph.addRoad(0, 1, 0.4, 40, false);
        mapGraph.addRoad(0, 4, 0.5, 35, false);
        mapGraph.addRoad(1, 4, 0.3, 30, false);
        mapGraph.addRoad(1, 2, 1.2, 50, false);
        mapGraph.addRoad(2, 3, 0.4, 25, false);
        mapGraph.addRoad(4, 3, 0.7, 30, true);
    }
}
