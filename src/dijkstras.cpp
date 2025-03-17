#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    const int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distances[source] = 0;
    pq.emplace(0, source);
    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (!visited[v] && current_dist + weight < distances[v]) {
                distances[v] = current_dist + weight;
                previous[v] = u;
                pq.emplace(distances[v], v);
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}