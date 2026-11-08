# Map Navigation System

SPL-1 Project (2026)  
Institute of Information Technology (IIT), University of Dhaka  
Name: Nilay Kumar Biswas  
Roll: 1710  

## Overview
This is a C++ project that calculates shortest paths between locations using Dijkstra's algorithm. Locations are represented as graph nodes and roads as weighted edges (distance in km). Roads can be dynamically marked open or closed.

All data structures (graph, adjacency list, and min-heap priority queue) and Dijkstra's algorithm are implemented from scratch without external libraries.

## Features
- Custom min-heap priority queue for Dijkstra's algorithm
- Real-time road status management (blocking/unblocking roads and recalculating routes)
- File handling to save and load map data
- Coordinates (x, y) included with each location for Qt GUI integration later
- Preloaded sample map of Dhaka University campus / IIT area

## How to Run

Compile with g++:
```bash
g++ -std=c++17 main.cpp -o main.exe
```

Run:
```bash
./main.exe
```
