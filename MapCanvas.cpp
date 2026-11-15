#include "MapCanvas.h"
#include <QPainterPath>

MapCanvas::MapCanvas(QWidget* parent)
    : QWidget(parent), graph(nullptr) {
    setMinimumSize(700, 600);
    setStyleSheet("background-color: #ffffff; border-radius: 8px;");
}

void MapCanvas::setGraph(const Graph* g) {
    graph = g;
    update();
}

void MapCanvas::setHighlightedPath(const std::vector<int>& path) {
    highlightedPath = path;
    update();
}

void MapCanvas::clearHighlight() {
    highlightedPath.clear();
    update();
}

void MapCanvas::paintEvent(QPaintEvent* /*event*/) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    // Draw background
    painter.fillRect(rect(), QColor("#fcfdfe"));

    if (!graph) return;

    const auto& locations = graph->getAllLocations();
    auto roads = graph->getAllRoads();

    // 1. Draw Roads (edges)
    for (const auto& r : roads) {
        if (r.u >= (int)locations.size() || r.v >= (int)locations.size()) continue;

        QPointF p1(locations[r.u].x, locations[r.u].y);
        QPointF p2(locations[r.v].x, locations[r.v].y);

        if (!r.isOpen) {
            // Blocked road (dashed red)
            QPen pen(QColor("#e74c3c"), 2, Qt::DashLine);
            painter.setPen(pen);
        } else {
            // Normal open road (slate blue)
            QPen pen(QColor("#7f8c8d"), 2, Qt::SolidLine);
            painter.setPen(pen);
        }

        painter.drawLine(p1, p2);
    }

    // 2. Draw Locations (nodes)
    const int radius = 14;
    QFont nodeFont("Arial", 8, QFont::Bold);
    QFont labelFont("Arial", 8);

    for (const auto& loc : locations) {
        QPointF pt(loc.x, loc.y);

        // Node circle outer border
        painter.setPen(QPen(QColor("#2c3e50"), 2));
        painter.setBrush(QBrush(QColor("#3498db")));
        painter.drawEllipse(pt, radius, radius);

        // Node ID number inside circle
        painter.setPen(Qt::white);
        painter.setFont(nodeFont);
        painter.drawText(QRectF(pt.x() - radius, pt.y() - radius, radius * 2, radius * 2),
                         Qt::AlignCenter, QString::number(loc.id));

        // Location Name label below node
        painter.setPen(QColor("#2c3e50"));
        painter.setFont(labelFont);
        QString label = QString::fromStdString(loc.name);
        painter.drawText(QRectF(pt.x() - 60, pt.y() + radius + 2, 120, 20),
                         Qt::AlignHCenter | Qt::AlignTop, label);
    }
}
