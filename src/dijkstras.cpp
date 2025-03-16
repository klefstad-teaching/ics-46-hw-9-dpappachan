#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (curr_dist > distances[u]) continue;

        for (const Edge& edge : G[u]) {
            int v = edge.dst, weight = edge.weight;
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path; 

    for (int at = destination; at != -1; at = previous[at])
        path.push_back(at);

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
