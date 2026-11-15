#include "MapCanvas.h"
#include <QPainterPath>
#include <cmath>

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

    QFont distFont("Arial", 7, QFont::DemiBold);
    QFont nodeFont("Arial", 8, QFont::Bold);
    QFont labelFont("Arial", 8);

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
            // Normal open road (slate gray)
            QPen pen(QColor("#7f8c8d"), 2, Qt::SolidLine);
            painter.setPen(pen);
        }

        painter.drawLine(p1, p2);

        // Draw directional arrow if one-way
        if (r.isOneWay) {
            double dx = p2.x() - p1.x();
            double dy = p2.y() - p1.y();
            double len = std::sqrt(dx * dx + dy * dy);
            if (len > 0.001) {
                double ux = dx / len;
                double uy = dy / len;

                // Arrow position at 65% of the road length
                QPointF arrowHead(p1.x() + 0.65 * dx, p1.y() + 0.65 * dy);
                double arrowSize = 9.0;

                // Wing perpendiculars
                QPointF wing1(arrowHead.x() - arrowSize * ux + (arrowSize * 0.5) * uy,
                              arrowHead.y() - arrowSize * uy - (arrowSize * 0.5) * ux);
                QPointF wing2(arrowHead.x() - arrowSize * ux - (arrowSize * 0.5) * uy,
                              arrowHead.y() - arrowSize * uy + (arrowSize * 0.5) * ux);

                QPolygonF arrowPoly;
                arrowPoly << arrowHead << wing1 << wing2;

                painter.setBrush(QBrush(r.isOpen ? QColor("#e67e22") : QColor("#e74c3c")));
                painter.setPen(Qt::NoPen);
                painter.drawPolygon(arrowPoly);
            }
        }

        // Draw distance tag at midpoint
        QPointF mid((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);
        QString distText = QString::number(r.weight, 'f', 1) + "km";

        // Draw small background pill for distance text
        painter.setFont(distFont);
        QFontMetrics fm(distFont);
        int textW = fm.horizontalAdvance(distText) + 6;
        int textH = fm.height() + 2;
        QRectF pillRect(mid.x() - textW / 2.0, mid.y() - textH / 2.0, textW, textH);

        painter.setPen(QPen(QColor("#bdc3c7"), 1));
        painter.setBrush(QBrush(QColor("#ffffff")));
        painter.drawRoundedRect(pillRect, 3, 3);

        painter.setPen(r.isOpen ? QColor("#555555") : QColor("#c0392b"));
        painter.drawText(pillRect, Qt::AlignCenter, distText);
    }

    // 2. Draw Locations (nodes)
    const int radius = 14;

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

        // Location Name label below node with semi-transparent background for readability
        painter.setFont(labelFont);
        QString label = QString::fromStdString(loc.name);
        QFontMetrics lfm(labelFont);
        int lw = lfm.horizontalAdvance(label) + 6;
        int lh = lfm.height();

        QRectF nameRect(pt.x() - lw / 2.0, pt.y() + radius + 3, lw, lh);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 255, 255, 200));
        painter.drawRoundedRect(nameRect, 2, 2);

        painter.setPen(QColor("#2c3e50"));
        painter.drawText(nameRect, Qt::AlignCenter, label);
    }
}
