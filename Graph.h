#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "Location.h"

using namespace std;

struct Edge {
    int to;
    double weight;     // distance in km
    double speedLimit; // speed limit in km/h
    bool isOneWay;     // true if one-way from u to v
    bool isOpen;       // false if blocked
};

struct RouteSegment {
    int from;
    int to;
    double distance;
    double speedLimit;
    double timeMinutes;
};

struct RouteResult {
    bool reachable;
    double totalDistance;
    double totalTimeMinutes;
    vector<int> path;
    vector<RouteSegment> segments;
    int nodesExplored;
};

class Graph {
private:
    int n;
    vector<Location> locations;
    vector<vector<Edge>> adj;

    double heuristic(int u, int target);
    void printRouteSummary(const RouteResult& res, const string& algoName);

public:
    Graph();

    void clear();
    int addLocation(string name, double x = 0.0, double y = 0.0);
    void addRoad(int u, int v, double weight, double speedLimit = 30.0, bool isOneWay = false, bool open = true);
    void setRoadStatus(int u, int v, bool open);
    
    // Shortest path algorithms with ETA
    RouteResult dijkstra(int src, int dest, bool display = true);
    RouteResult aStar(int src, int dest, bool display = true);
    void compareAlgorithms(int src, int dest);

    void showLocations();
    void showRoads();
    bool saveFile(string filename);
    bool loadFile(string filename);
    int getLocationCount();
    Location getLocation(int id);
};

#endif
