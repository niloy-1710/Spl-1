#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Location.h"

using namespace std;

struct Edge {
    int to;
    double weight;     // distance in km
    double speedLimit; // speed limit in km/h
    bool isOneWay;     // true if one-way from u to v
    bool isOpen;       // false if blocked
};

class Graph {
private:
    int n;
    vector<Location> locations;
    vector<vector<Edge>> adj;

public:
    Graph();

    void clear();
    int addLocation(string name, double x = 0.0, double y = 0.0);
    void addRoad(int u, int v, double weight, double speedLimit = 30.0, bool isOneWay = false, bool open = true);
    void setRoadStatus(int u, int v, bool open);
    void dijkstra(int src, int dest);
    void showLocations();
    void showRoads();
    bool saveFile(string filename);
    bool loadFile(string filename);
    int getLocationCount();
    Location getLocation(int id);
};

#endif
