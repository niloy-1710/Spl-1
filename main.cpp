#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>

using namespace std;

struct Edge {
    int to;
    int weight;
    bool isOpen;
};

class Graph {
private:
    int n;
    vector<string> names;
    vector<vector<Edge>> adj;

public:
    Graph() : n(0) {}

    int addLocation(string name) {
        names.push_back(name);
        adj.push_back({});
        return n++;
    }

    void addRoad(int u, int v, int w, bool open = true) {
        adj[u].push_back({v, w, open});
        adj[v].push_back({u, w, open});
    }

    void setRoadStatus(int u, int v, bool open) {
        for (auto &e : adj[u]) if (e.to == v) e.isOpen = open;
        for (auto &e : adj[v]) if (e.to == u) e.isOpen = open;
    }

    void dijkstra(int src, int dest) {
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);

        dist[src] = 0;

        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                    u = j;
            }

            if (u == -1 || dist[u] == INT_MAX) break;
            visited[u] = true;
            if (u == dest) break;

            for (auto &e : adj[u]) {
                if (!e.isOpen) continue; // skip blocked roads
                if (dist[u] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[u] + e.weight;
                    parent[e.to] = u;
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No path found between " << names[src] << " and " << names[dest] << "\n";
            return;
        }

        cout << "Shortest distance: " << dist[dest] << " km\nRoute: ";
        vector<int> path;
        for (int curr = dest; curr != -1; curr = parent[curr])
            path.push_back(curr);

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << names[path[i]] << (i > 0 ? " -> " : "\n");
        }
    }

    void showLocations() {
        cout << "\nLocations:\n";
        for (int i = 0; i < n; i++)
            cout << i << ": " << names[i] << "\n";
    }

    void showRoads() {
        cout << "\nRoads:\n";
        for (int u = 0; u < n; u++) {
            for (auto &e : adj[u]) {
                if (u < e.to) {
                    cout << names[u] << " <-> " << names[e.to] 
                         << " (" << e.weight << " km) [" 
                         << (e.isOpen ? "OPEN" : "BLOCKED") << "]\n";
                }
            }
        }
    }

    void saveFile(string filename) {
        ofstream out(filename);
        out << n << "\n";
        for (int i = 0; i < n; i++) out << names[i] << "\n";

        for (int u = 0; u < n; u++) {
            for (auto &e : adj[u]) {
                if (u < e.to)
                    out << u << " " << e.to << " " << e.weight << " " << e.isOpen << "\n";
            }
        }
        cout << "Saved to " << filename << "\n";
    }

    void loadFile(string filename) {
        ifstream in(filename);
        if (!in) { cout << "File not found.\n"; return; }
        in >> n;
        names.resize(n);
        adj.assign(n, {});
        for (int i = 0; i < n; i++) in >> names[i];

        int u, v, w, open;
        while (in >> u >> v >> w >> open) addRoad(u, v, w, open);
        cout << "Loaded from " << filename << "\n";
    }
};

int main() {
    Graph g;

    // sample DU landmarks
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

        if (choice == 1) g.showLocations();
        else if (choice == 2) g.showRoads();
        else if (choice == 3) {
            int s, d;
            cout << "Enter start and destination ID: ";
            cin >> s >> d;
            g.dijkstra(s, d);
        }
        else if (choice == 4) {
            int u, v, status;
            cout << "Enter u, v and status (1: open, 0: close): ";
            cin >> u >> v >> status;
            g.setRoadStatus(u, v, status == 1);
        }
        else if (choice == 5) g.saveFile("map.txt");
        else if (choice == 6) g.loadFile("map.txt");
    }

    return 0;
}
