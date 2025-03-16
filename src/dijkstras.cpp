#include <algorithm>
#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    distances[source] = 0;
    pq.push({source, 0});
    while (!pq.empty()) {

        Node current =pq.top();
        pq.pop();
        int u = current.vertex;

        if (current.weight > distances[u]) continue;
        for (const Edge & e : G[u]) {
            int v = e.dst, weight = e.weight;

            if (distances[u] + weight < distances[v]) {

                distances[v]= distances[u]+weight;

                previous[v] = u;
                pq.push({v, distances[v]});
            }
        }
    }
    return distances;
}



vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path;
    }

    for (int at = destination; at != -1; at = previous[at]){
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}


void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i]<< " ";
    }
    cout << "\nTotal cost is " << total << endl;
}