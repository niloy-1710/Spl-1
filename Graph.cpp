#include "Graph.h"
#include "MinHeap.h"

Graph::Graph() : n(0) {}

void Graph::clear() {
    n = 0;
    locations.clear();
    adj.clear();
}

int Graph::addLocation(string name, double x, double y) {
    int id = n++;
    locations.push_back(Location(id, name, x, y));
    adj.push_back({});
    return id;
}

void Graph::addRoad(int u, int v, double weight, double speedLimit, bool isOneWay, bool open) {
    if (u < 0 || u >= n || v < 0 || v >= n) return;
    adj[u].push_back({v, weight, speedLimit, isOneWay, open});
    if (!isOneWay) {
        adj[v].push_back({u, weight, speedLimit, false, open});
    }
}

void Graph::setRoadStatus(int u, int v, bool open) {
    if (u < 0 || u >= n || v < 0 || v >= n) return;
    for (auto &e : adj[u]) {
        if (e.to == v) e.isOpen = open;
    }
    for (auto &e : adj[v]) {
        if (e.to == u && !e.isOneWay) e.isOpen = open;
    }
}

// dijkstra shortest path
void Graph::dijkstra(int src, int dest) {
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        cout << "Invalid location ID.\n";
        return;
    }

    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    MinHeap pq;
    dist[src] = 0.0;
    pq.push(src, 0.0);

    while (!pq.empty()) {
        HeapNode cur = pq.pop();
        int u = cur.vertex;

        if (visited[u]) continue;
        visited[u] = true;

        if (u == dest) break;

        for (auto &e : adj[u]) {
            if (!e.isOpen) continue; // skip blocked roads

            int v = e.to;
            double w = e.weight;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(v, dist[v]);
            }
        }
    }

    if (dist[dest] >= INF) {
        cout << "No active path found between " << locations[src].name << " and " << locations[dest].name << "\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "Shortest distance: " << dist[dest] << " km\nRoute: ";
    vector<int> path;
    for (int curr = dest; curr != -1; curr = parent[curr])
        path.push_back(curr);

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << locations[path[i]].name << (i > 0 ? " -> " : "\n");
    }
}

void Graph::showLocations() {
    cout << "\nLocations:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": " << locations[i].name 
             << " (" << locations[i].x << ", " << locations[i].y << ")\n";
    }
}

void Graph::showRoads() {
    cout << "\nRoads:\n";
    for (int u = 0; u < n; u++) {
        for (auto &e : adj[u]) {
            // print one-way or only print two-way once (u < e.to)
            if (e.isOneWay) {
                cout << locations[u].name << " -> " << locations[e.to].name 
                     << " [One-Way, " << fixed << setprecision(1) << e.weight << " km, " 
                     << (int)e.speedLimit << " km/h] [" 
                     << (e.isOpen ? "OPEN" : "BLOCKED") << "]\n";
            } else if (u < e.to) {
                cout << locations[u].name << " <-> " << locations[e.to].name 
                     << " [Two-Way, " << fixed << setprecision(1) << e.weight << " km, " 
                     << (int)e.speedLimit << " km/h] [" 
                     << (e.isOpen ? "OPEN" : "BLOCKED") << "]\n";
            }
        }
    }
}

bool Graph::saveFile(string filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error: could not open " << filename << " for saving.\n";
        return false;
    }

    out << "[LOCATIONS]\n";
    out << n << "\n";
    for (int i = 0; i < n; i++) {
        out << locations[i].name << " " << locations[i].x << " " << locations[i].y << "\n";
    }

    int roadCount = 0;
    for (int u = 0; u < n; u++) {
        for (auto &e : adj[u]) {
            if (e.isOneWay || u < e.to) roadCount++;
        }
    }

    out << "[ROADS]\n";
    out << roadCount << "\n";
    for (int u = 0; u < n; u++) {
        for (auto &e : adj[u]) {
            if (e.isOneWay || u < e.to) {
                out << u << " " << e.to << " " << e.weight << " " 
                    << e.speedLimit << " " << (e.isOneWay ? 1 : 0) << " " 
                    << (e.isOpen ? 1 : 0) << "\n";
            }
        }
    }

    out.close();
    cout << "Map saved to " << filename << " successfully.\n";
    return true;
}

bool Graph::loadFile(string filename) {
    ifstream in(filename);
    if (!in) {
        cout << "Error: file " << filename << " not found.\n";
        return false;
    }

    string line;
    clear();

    while (getline(in, line)) {
        if (line == "[LOCATIONS]") {
            int locCount;
            if (!(in >> locCount)) break;
            for (int i = 0; i < locCount; i++) {
                string name;
                double x, y;
                in >> name >> x >> y;
                addLocation(name, x, y);
            }
        } else if (line == "[ROADS]") {
            int roadCount;
            if (!(in >> roadCount)) break;
            for (int i = 0; i < roadCount; i++) {
                int u, v, oneWay, open;
                double w, speed;
                in >> u >> v >> w >> speed >> oneWay >> open;
                addRoad(u, v, w, speed, oneWay == 1, open == 1);
            }
        }
    }

    in.close();
    cout << "Loaded map with " << n << " locations from " << filename << "\n";
    return true;
}

int Graph::getLocationCount() {
    return n;
}

Location Graph::getLocation(int id) {
    if (id >= 0 && id < n) return locations[id];
    return Location();
}
