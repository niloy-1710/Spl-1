#ifndef LOCATION_H
#define LOCATION_H

#include <string>

using namespace std;

// represents a map node with coordinates for gui
struct Location {
    int id;
    string name;
    double x;
    double y;

    Location() : id(-1), name(""), x(0.0), y(0.0) {}
    Location(int id, string name, double x = 0.0, double y = 0.0)
        : id(id), name(name), x(x), y(y) {}
};

#endif

