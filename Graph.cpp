#include "Graph.h"
#include "MinHeap.h"

Graph::Graph() : n(0) {}

int Graph::addLocation(string name, double x, double y) {
    int id = n++;
    locations.push_back(Location(id, name, x, y));
    adj.push_back({});
    return id;
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

// dijkstra using custom min-heap
void Graph::dijkstra(int src, int dest) {
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        cout << "Invalid location ID.\n";
        return;
    }

    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    MinHeap pq;
    dist[src] = 0;
    pq.push(src, 0);

    while (!pq.empty()) {
        HeapNode cur = pq.pop();
        int u = cur.vertex;

        if (visited[u]) continue;
        visited[u] = true;

        if (u == dest) break;

        for (auto &e : adj[u]) {
            if (!e.isOpen) continue; // skip blocked roads

            int v = e.to;
            int w = e.weight;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(v, dist[v]);
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path found between " << locations[src].name << " and " << locations[dest].name << "\n";
        return;
    }

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
            if (u < e.to) {
                cout << locations[u].name << " <-> " << locations[e.to].name 
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
    for (int i = 0; i < n; i++) {
        out << locations[i].name << " " << locations[i].x << " " << locations[i].y << "\n";
    }

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
    locations.clear();
    adj.assign(n, {});

    for (int i = 0; i < n; i++) {
        string name;
        double x, y;
        in >> name >> x >> y;
        locations.push_back(Location(i, name, x, y));
    }

    int u, v, w, open;
    while (in >> u >> v >> w >> open) {
        addRoad(u, v, w, open);
    }
    cout << "Loaded from " << filename << "\n";
}

int Graph::getLocationCount() {
    return n;
}

Location Graph::getLocation(int id) {
    if (id >= 0 && id < n) return locations[id];
    return Location();
}
