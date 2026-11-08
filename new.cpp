#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int v)
    {
        vertices = v;
        adj.resize(v);
    }

    void addRoad(int u, int v, int distance)
    {
        adj[u].push_back({v, distance});
        adj[v].push_back({u, distance});
    }

    void dijkstra(int source)
    {
        vector<int> distance(vertices, INT_MAX);
        vector<bool> visited(vertices, false);

        distance[source] = 0;

        for (int i = 0; i < vertices; i++)
        {
            int u = -1;

            for (int j = 0; j < vertices; j++)
            {
                if (!visited[j] &&
                    (u == -1 || distance[j] < distance[u]))
                {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (auto edge : adj[u])
            {
                int v = edge.first;
                int weight = edge.second;

                if (distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                }
            }
        }

        cout << "\nShortest distances from location " << source << ":\n";

        for (int i = 0; i < vertices; i++)
        {
            cout << "Location " << i << ": ";

            if (distance[i] == INT_MAX)
                cout << "Unreachable\n";
            else
                cout << distance[i] << " km\n";
        }
    }
};

int main()
{

    Graph map(5);

    map.addRoad(0, 1, 4);
    map.addRoad(0, 2, 2);
    map.addRoad(1, 2, 1);
    map.addRoad(1, 3, 5);
    map.addRoad(2, 3, 8);
    map.addRoad(2, 4, 10);
    map.addRoad(3, 4, 2);

    cout << "===== Map Navigation System =====\n";

    int source;
    cout << "Enter starting location (0-4): ";
    cin >> source;

    map.dijkstra(source);

    return 0;
}