#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Map Navigation System - SPL 1 (IIT DU)");
    resize(1100, 750);

    setupUI();
    loadSampleData();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    // Control panel sidebar
    controlPanelLayout = new QVBoxLayout();
    titleLabel = new QLabel("<h2>Map Navigation</h2><p>Dhaka University Campus</p>", this);
    controlPanelLayout->addWidget(titleLabel);

    controlPanelLayout->addStretch();

    // Placeholder for map display area (will become MapCanvas in next commit)
    QLabel* placeholder = new QLabel("Map View Canvas\n(Visual interactive map of DU Campus)", this);
    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setStyleSheet("background-color: #f7f9fb; border: 2px dashed #b0b8c4; font-size: 16px; border-radius: 8px; color: #555;");

    mainLayout->addWidget(placeholder, 3); // 75% width
    mainLayout->addLayout(controlPanelLayout, 1); // 25% width

    statusBar()->showMessage("System Ready | 24 Locations Loaded from map.txt");
}

void MainWindow::loadSampleData() {
    if (!mapGraph.loadFile("map.txt")) {
        // Fallback default landmarks if map.txt is not found
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
