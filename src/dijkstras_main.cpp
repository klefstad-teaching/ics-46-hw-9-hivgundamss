#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

int main(){
    Graph G;
    file_to_graph("./src/small.txt", G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for (int dest = 0; dest < G.numVertices; ++dest) {
        vector<int> path = extract_shortest_path(distances, previous, dest);
        int total_cost = (dest == 0) ? 0 : distances[dest];
        
        print_path(path, total_cost);
    }
}