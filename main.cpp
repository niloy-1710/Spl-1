#include "Graph.h"

int main() {
    Graph g;

    // default Dhaka University landmarks
    g.addLocation("IIT");
    g.addLocation("Curzon");
    g.addLocation("TSC");
    g.addLocation("Central_Library");
    g.addLocation("Shaheed_Minar");

    g.addRoad(0, 1, 4); // IIT - Curzon
    g.addRoad(0, 4, 3); // IIT - Shaheed Minar
    g.addRoad(1, 4, 2); // Curzon - Shaheed Minar
    g.addRoad(4, 3, 5); // Shaheed Minar - Central Library
    g.addRoad(3, 2, 2); // Central Library - TSC
    g.addRoad(1, 2, 8); // Curzon - TSC

    int choice;
    while (true) {
        cout << "\n1. Locations  2. Roads  3. Shortest Route  4. Block/Open Road  5. Save  6. Load  0. Exit\nChoice: ";
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
            int u, v, status;
            cout << "Enter u, v and status (1: open, 0: close): ";
            cin >> u >> v >> status;
            g.setRoadStatus(u, v, status == 1);
        } else if (choice == 5) {
            g.saveFile("map.txt");
        } else if (choice == 6) {
            g.loadFile("map.txt");
        }
    }

    return 0;
}
