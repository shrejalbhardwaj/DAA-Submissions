#include <iostream>
#include <climits>
using namespace std;

#define MAX 100

void dijkstra(int graph[MAX][MAX], int V, int source, int dist[])
{
    bool visited[MAX];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[source] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int minDist = INT_MAX;
        int u = -1;

        // Find vertex with minimum distance
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = true;

        // Update distances of adjacent vertices
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main()
{
    int V, E;

    int graph[MAX][MAX] = {0};

    cout << "Enter number of intersections (vertices): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    cout << "Enter roads (u v time):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        graph[u][v] = w;
        graph[v][u] = w;
    }

    int source;

    cout << "Enter ambulance start location: ";
    cin >> source;

    int H;

    cout << "Enter number of hospitals: ";
    cin >> H;

    int hospitals[MAX];

    cout << "Enter hospital nodes: ";

    for (int i = 0; i < H; i++)
    {
        cin >> hospitals[i];
    }

    int dist[MAX];

    dijkstra(graph, V, source, dist);

    int minTime = INT_MAX;
    int nearestHospital = -1;

    for (int i = 0; i < H; i++)
    {
        int h = hospitals[i];

        if (dist[h] < minTime)
        {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1 ||
        minTime == INT_MAX)
    {
        cout << "No hospital reachable.\n";
    }
    else
    {
        cout << "\nNearest hospital is at node "
             << nearestHospital
             << " with travel time "
             << minTime
             << " minutes.\n";
    }

    return 0;
}
