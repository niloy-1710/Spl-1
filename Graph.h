#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include "Location.h"

using namespace std;

struct Edge {
    int to;
    int weight;
    bool isOpen;
};

class Graph {
private:
    int n;
    vector<Location> locations;
    vector<vector<Edge>> adj;

public:
    Graph();

    int addLocation(string name, double x = 0.0, double y = 0.0);
    void addRoad(int u, int v, int weight, bool open = true);
    void setRoadStatus(int u, int v, bool open);
    void dijkstra(int src, int dest);
    void showLocations();
    void showRoads();
    void saveFile(string filename);
    void loadFile(string filename);
    int getLocationCount();
    Location getLocation(int id);
};

#endif
