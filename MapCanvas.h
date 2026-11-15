#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <vector>
#include "Graph.h"

class MapCanvas : public QWidget {
    Q_OBJECT

private:
    const Graph* graph;
    std::vector<int> highlightedPath;

protected:
    void paintEvent(QPaintEvent* event) override;

public:
    explicit MapCanvas(QWidget* parent = nullptr);
    void setGraph(const Graph* g);
    void setHighlightedPath(const std::vector<int>& path);
    void clearHighlight();
};

#endif
