#include <iostream>
#include <cassert>
#include <cmath>
#include "Graph.h"
#include "MinHeap.h"

using namespace std;

// Helper to compare floating point numbers
bool approxEqual(double a, double b, double eps = 0.001) {
    return fabs(a - b) < eps;
}

// Test 1: MinHeap priority queue property
void testMinHeap() {
    cout << "[TEST 1] Testing custom MinHeap ordering... ";
    MinHeap pq;
    pq.push(1, 15.5);
    pq.push(2, 3.2);
    pq.push(3, 8.7);
    pq.push(4, 1.1);

    assert(pq.pop().vertex == 4); // smallest 1.1
    assert(pq.pop().vertex == 2); // next 3.2
    assert(pq.pop().vertex == 3); // next 8.7
    assert(pq.pop().vertex == 1); // largest 15.5
    assert(pq.empty());
    cout << "PASSED\n";
}

// Test 2: Standard shortest path accuracy
void testShortestPathAccuracy() {
    cout << "[TEST 2] Testing shortest path accuracy (Dijkstra vs A*)... ";
    Graph g;
    g.addLocation("A", 0, 0);   // 0
    g.addLocation("B", 10, 0);  // 1
    g.addLocation("C", 20, 0);  // 2
    g.addLocation("D", 10, 10); // 3

    g.addRoad(0, 1, 4.0, 40, false);
    g.addRoad(1, 2, 3.0, 40, false);
    g.addRoad(0, 3, 10.0, 40, false);
    g.addRoad(3, 2, 2.0, 40, false);

    // Path A -> B -> C should be 4 + 3 = 7 km (shorter than A -> D -> C: 10 + 2 = 12 km)
    RouteResult rDijkstra = g.dijkstra(0, 2, false);
    RouteResult rAStar = g.aStar(0, 2, false);

    assert(rDijkstra.reachable);
    assert(rAStar.reachable);
    assert(approxEqual(rDijkstra.totalDistance, 7.0));
    assert(approxEqual(rAStar.totalDistance, 7.0));
    assert(rDijkstra.path.size() == 3);
    assert(rDijkstra.path[0] == 0 && rDijkstra.path[1] == 1 && rDijkstra.path[2] == 2);
    cout << "PASSED\n";
}

// Test 3: Road status dynamic exclusion and rerouting
void testRoadExclusionRerouting() {
    cout << "[TEST 3] Testing dynamic road blocking and rerouting... ";
    Graph g;
    g.addLocation("A", 0, 0);
    g.addLocation("B", 10, 0);
    g.addLocation("C", 20, 0);
    g.addLocation("D", 10, 10);

    g.addRoad(0, 1, 4.0, 40, false);
    g.addRoad(1, 2, 3.0, 40, false);
    g.addRoad(0, 3, 10.0, 40, false);
    g.addRoad(3, 2, 2.0, 40, false);

    // Block road between B (1) and C (2)
    g.setRoadStatus(1, 2, false);

    // Now shortest path must dynamically reroute through D: A -> D -> C (12.0 km)
    RouteResult r = g.dijkstra(0, 2, false);
    assert(r.reachable);
    assert(approxEqual(r.totalDistance, 12.0));
    assert(r.path.size() == 3);
    assert(r.path[0] == 0 && r.path[1] == 3 && r.path[2] == 2);
    cout << "PASSED\n";
}

// Test 4: Disconnected graph / completely blocked route
void testUnreachableDestination() {
    cout << "[TEST 4] Testing disconnected path handling... ";
    Graph g;
    g.addLocation("Island1", 0, 0); // 0
    g.addLocation("Island2", 10, 10); // 1
    g.addLocation("Isolated", 50, 50); // 2

    g.addRoad(0, 1, 5.0, 40, false);

    // Node 2 has no edges connected
    RouteResult r = g.dijkstra(0, 2, false);
    assert(!r.reachable);
    assert(r.path.empty());
    cout << "PASSED\n";
}

// Test 5: One-way road traffic direction enforcement
void testOneWayRoadCompliance() {
    cout << "[TEST 5] Testing one-way direction enforcement... ";
    Graph g;
    g.addLocation("Start", 0, 0); // 0
    g.addLocation("End", 10, 0);   // 1

    // One-way from 0 -> 1
    g.addRoad(0, 1, 2.0, 40, true);

    // 0 -> 1 should succeed
    RouteResult forward = g.dijkstra(0, 1, false);
    assert(forward.reachable);
    assert(approxEqual(forward.totalDistance, 2.0));

    // 1 -> 0 should fail (illegal travel against one-way)
    RouteResult reverse = g.dijkstra(1, 0, false);
    assert(!reverse.reachable);
    cout << "PASSED\n";
}

// Test 6: Source equals destination (zero distance)
void testSameSourceDestination() {
    cout << "[TEST 6] Testing source == destination... ";
    Graph g;
    g.addLocation("Home", 10, 10);
    RouteResult r = g.dijkstra(0, 0, false);
    assert(r.reachable);
    assert(approxEqual(r.totalDistance, 0.0));
    assert(r.path.size() == 1 && r.path[0] == 0);
    cout << "PASSED\n";
}

int main() {
    cout << "=========================================\n";
    cout << "      RUNNING SPL-1 UNIT TEST SUITE      \n";
    cout << "=========================================\n";

    testMinHeap();
    testShortestPathAccuracy();
    testRoadExclusionRerouting();
    testUnreachableDestination();
    testOneWayRoadCompliance();
    testSameSourceDestination();

    cout << "=========================================\n";
    cout << "  ALL 6 UNIT TESTS PASSED SUCCESSFULLY!  \n";
    cout << "=========================================\n";

    return 0;
}

