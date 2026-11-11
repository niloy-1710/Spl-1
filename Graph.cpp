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

// Euclidean distance heuristic for A* (admissible: h <= true distance)
double Graph::heuristic(int u, int target) {
    if (u < 0 || u >= n || target < 0 || target >= n) return 0.0;
    double dx = locations[u].x - locations[target].x;
    double dy = locations[u].y - locations[target].y;
    return sqrt(dx * dx + dy * dy) * 0.002;
}

// Format and display complete route summary with ETA
void Graph::printRouteSummary(const RouteResult& res, const string& algoName) {
    if (!res.reachable) {
        cout << "\n[" << algoName << "] No active path found.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n========================================================\n";
    cout << "             ROUTE SUMMARY (" << algoName << ")\n";
    cout << "========================================================\n";
    cout << "Start       : " << locations[res.path.front()].name << "\n";
    cout << "Destination : " << locations[res.path.back()].name << "\n";
    cout << "Total Dist. : " << res.totalDistance << " km\n";
    cout << "Est. Time   : " << res.totalTimeMinutes << " mins (" 
         << (int)res.totalTimeMinutes << "m " << (int)((res.totalTimeMinutes - (int)res.totalTimeMinutes) * 60) << "s)\n";
    cout << "Nodes Visited: " << res.nodesExplored << "\n";
    cout << "--------------------------------------------------------\n";
    cout << "Turn-by-Turn Directions:\n";

    for (size_t i = 0; i < res.segments.size(); i++) {
        const auto& seg = res.segments[i];
        cout << "  " << (i + 1) << ". " << locations[seg.from].name 
             << " -> " << locations[seg.to].name 
             << " [" << seg.distance << " km, " << (int)seg.speedLimit << " km/h, ~" 
             << seg.timeMinutes << " mins]\n";
    }
    cout << "========================================================\n";
}

// Dijkstra shortest path with ETA calculation
RouteResult Graph::dijkstra(int src, int dest, bool display) {
    RouteResult result = {false, 0.0, 0.0, {}, {}, 0};
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        cout << "Invalid location ID.\n";
        return result;
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
        result.nodesExplored++;

        if (u == dest) break;

        for (auto &e : adj[u]) {
            if (!e.isOpen) continue;

            int v = e.to;
            double w = e.weight;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(v, dist[v]);
            }
        }
    }

    if (dist[dest] < INF) {
        result.reachable = true;
        result.totalDistance = dist[dest];

        // Reconstruct path
        for (int curr = dest; curr != -1; curr = parent[curr])
            result.path.push_back(curr);
        
        // Reverse
        int l = 0, r = result.path.size() - 1;
        while (l < r) {
            swap(result.path[l], result.path[r]);
            l++;
            r--;
        }

        // Calculate segment times and speeds
        for (size_t i = 0; i + 1 < result.path.size(); i++) {
            int u = result.path[i];
            int v = result.path[i + 1];
            double d = 0.0, sp = 30.0;
            for (auto &e : adj[u]) {
                if (e.to == v) {
                    d = e.weight;
                    sp = e.speedLimit;
                    break;
                }
            }
            double tMins = (sp > 0) ? (d / sp) * 60.0 : 0.0;
            result.totalTimeMinutes += tMins;
            result.segments.push_back({u, v, d, sp, tMins});
        }
    }

    if (display) {
        printRouteSummary(result, "Dijkstra");
    }

    return result;
}

// A* Search with ETA calculation
RouteResult Graph::aStar(int src, int dest, bool display) {
    RouteResult result = {false, 0.0, 0.0, {}, {}, 0};
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        cout << "Invalid location ID.\n";
        return result;
    }

    vector<double> gScore(n, INF);
    vector<double> fScore(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    MinHeap pq;
    gScore[src] = 0.0;
    fScore[src] = heuristic(src, dest);
    pq.push(src, fScore[src]);

    while (!pq.empty()) {
        HeapNode cur = pq.pop();
        int u = cur.vertex;

        if (visited[u]) continue;
        visited[u] = true;
        result.nodesExplored++;

        if (u == dest) break;

        for (auto &e : adj[u]) {
            if (!e.isOpen) continue;

            int v = e.to;
            double tentativeG = gScore[u] + e.weight;

            if (tentativeG < gScore[v]) {
                parent[v] = u;
                gScore[v] = tentativeG;
                fScore[v] = tentativeG + heuristic(v, dest);
                pq.push(v, fScore[v]);
            }
        }
    }

    if (gScore[dest] < INF) {
        result.reachable = true;
        result.totalDistance = gScore[dest];

        for (int curr = dest; curr != -1; curr = parent[curr])
            result.path.push_back(curr);

        int l = 0, r = result.path.size() - 1;
        while (l < r) {
            swap(result.path[l], result.path[r]);
            l++;
            r--;
        }

        for (size_t i = 0; i + 1 < result.path.size(); i++) {
            int u = result.path[i];
            int v = result.path[i + 1];
            double d = 0.0, sp = 30.0;
            for (auto &e : adj[u]) {
                if (e.to == v) {
                    d = e.weight;
                    sp = e.speedLimit;
                    break;
                }
            }
            double tMins = (sp > 0) ? (d / sp) * 60.0 : 0.0;
            result.totalTimeMinutes += tMins;
            result.segments.push_back({u, v, d, sp, tMins});
        }
    }

    if (display) {
        printRouteSummary(result, "A* Search");
    }

    return result;
}

// Side-by-side comparison
void Graph::compareAlgorithms(int src, int dest) {
    RouteResult r1 = dijkstra(src, dest, false);
    RouteResult r2 = aStar(src, dest, false);

    cout << fixed << setprecision(2);
    cout << "\n========================================================\n";
    cout << "     ALGORITHM COMPARISON: " << locations[src].name << " -> " << locations[dest].name << "\n";
    cout << "========================================================\n";
    cout << left << setw(18) << "Metric" << setw(18) << "Dijkstra" << setw(18) << "A* Search" << "\n";
    cout << "--------------------------------------------------------\n";
    cout << left << setw(18) << "Reachable" 
         << setw(18) << (r1.reachable ? "Yes" : "No") 
         << setw(18) << (r2.reachable ? "Yes" : "No") << "\n";
    cout << left << setw(18) << "Distance (km)" 
         << setw(18) << r1.totalDistance 
         << setw(18) << r2.totalDistance << "\n";
    cout << left << setw(18) << "ETA (mins)" 
         << setw(18) << r1.totalTimeMinutes 
         << setw(18) << r2.totalTimeMinutes << "\n";
    cout << left << setw(18) << "Nodes Explored" 
         << setw(18) << r1.nodesExplored 
         << setw(18) << r2.nodesExplored << "\n";
    cout << "========================================================\n";
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
