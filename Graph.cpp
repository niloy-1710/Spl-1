#include "Graph.h"

Graph::Graph() : n(0) {}

int Graph::addLocation(string name) {
    names.push_back(name);
    adj.push_back({});
    return n++;
}

void Graph::addRoad(int u, int v, int weight, bool open) {
    if (u < 0 || u >= n || v < 0 || v >= n) return;
    adj[u].push_back({v, weight, open});
    adj[v].push_back({u, weight, open});
}

void Graph::setRoadStatus(int u, int v, bool open) {
    if (u < 0 || u >= n || v < 0 || v >= n) return;
    for (auto &e : adj[u]) {
        if (e.to == v) e.isOpen = open;
    }
    for (auto &e : adj[v]) {
        if (e.to == u) e.isOpen = open;
    }
}

void Graph::dijkstra(int src, int dest) {
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        cout << "Invalid location ID.\n";
        return;
    }

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

void Graph::showLocations() {
    cout << "\nLocations:\n";
    for (int i = 0; i < n; i++)
        cout << i << ": " << names[i] << "\n";
}

void Graph::showRoads() {
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

void Graph::saveFile(string filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Could not open file for writing.\n";
        return;
    }

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

void Graph::loadFile(string filename) {
    ifstream in(filename);
    if (!in) {
        cout << "File not found.\n";
        return;
    }

    in >> n;
    names.resize(n);
    adj.assign(n, {});
    for (int i = 0; i < n; i++) in >> names[i];

    int u, v, w, open;
    while (in >> u >> v >> w >> open) {
        addRoad(u, v, w, open);
    }
    cout << "Loaded from " << filename << "\n";
}

int Graph::getLocationCount() {
    return n;
}

string Graph::getLocationName(int id) {
    if (id >= 0 && id < n) return names[id];
    return "";
}
