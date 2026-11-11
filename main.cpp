#include "Graph.h"

int main() {
    Graph g;

    // Dhaka University landmarks with coordinates
    g.addLocation("IIT", 250, 300);
    g.addLocation("Curzon", 380, 200);
    g.addLocation("TSC", 150, 120);
    g.addLocation("Central_Library", 200, 180);
    g.addLocation("Shaheed_Minar", 300, 260);

    // Roads: u, v, distance (km), speedLimit (km/h), isOneWay
    g.addRoad(0, 1, 0.4, 40, false); // IIT <-> Curzon (Two-Way, 40 km/h)
    g.addRoad(0, 4, 0.5, 35, false); // IIT <-> Shaheed Minar (Two-Way, 35 km/h)
    g.addRoad(1, 4, 0.3, 30, false); // Curzon <-> Shaheed Minar (Two-Way, 30 km/h)
    g.addRoad(1, 2, 1.2, 50, false); // Curzon <-> TSC (Two-Way, 50 km/h)
    g.addRoad(2, 3, 0.4, 25, false); // TSC <-> Central Library (Two-Way, 25 km/h)
    g.addRoad(4, 3, 0.7, 30, true);  // Shaheed Minar -> Central Library (One-Way, 30 km/h)

    int choice;
    while (true) {
        cout << "\n=========================================\n";
        cout << "      MAP NAVIGATION SYSTEM (SPL-1)      \n";
        cout << "=========================================\n";
        cout << "1. View Locations\n";
        cout << "2. View Roads & Speed Limits\n";
        cout << "3. Shortest Route & ETA (Dijkstra)\n";
        cout << "4. Shortest Route & ETA (A* Search)\n";
        cout << "5. Compare Dijkstra vs A*\n";
        cout << "6. Toggle Road Status (Open / Block)\n";
        cout << "7. Save Map to File\n";
        cout << "8. Load Map from File\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        if (!(cin >> choice) || choice == 0) break;

        if (choice == 1) {
            g.showLocations();
        } else if (choice == 2) {
            g.showRoads();
        } else if (choice == 3) {
            int s, d;
            cout << "Enter start and destination ID: ";
            cin >> s >> d;
            g.dijkstra(s, d);
        } else if (choice == 4) {
            int s, d;
            cout << "Enter start and destination ID: ";
            cin >> s >> d;
            g.aStar(s, d);
        } else if (choice == 5) {
            int s, d;
            cout << "Enter start and destination ID: ";
            cin >> s >> d;
            g.compareAlgorithms(s, d);
        } else if (choice == 6) {
            int u, v, status;
            cout << "Enter u, v and status (1: open, 0: close): ";
            cin >> u >> v >> status;
            g.setRoadStatus(u, v, status == 1);
        } else if (choice == 7) {
            g.saveFile("map.txt");
        } else if (choice == 8) {
            g.loadFile("map.txt");
        }
    }

    return 0;
}
