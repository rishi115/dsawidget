# Graph

A collection of vertices connected by edges.

## Time Complexity

| Operation | Adjacency List | Adjacency Matrix |
|-----------|----------------|------------------|
| Add Vertex | O(1) | O(V²) |
| Add Edge | O(1) | O(1) |
| Remove Edge | O(E) | O(1) |
| Check Edge | O(V) | O(1) |
| BFS/DFS | O(V + E) | O(V²) |
| Dijkstra | O((V+E) log V) | O(V²) |

## Implementation (Adjacency List)

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <climits>
using namespace std;

class Graph {
private:
    int V;
    vector<list<pair<int, int>>> adj;  // {neighbor, weight}
    bool directed;

public:
    Graph(int vertices, bool isDirected = false) {
        V = vertices;
        adj.resize(V);
        directed = isDirected;
    }

    void addEdge(int u, int v, int weight = 1) {
        adj[u].push_back({v, weight});
        if (!directed) adj[v].push_back({u, weight});
    }

    // BFS - O(V + E)
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS: ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (auto& p : adj[u]) {
                if (!visited[p.first]) {
                    visited[p.first] = true;
                    q.push(p.first);
                }
            }
        }
        cout << endl;
    }

    // DFS - O(V + E)
    void DFSUtil(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        for (auto& p : adj[u]) {
            if (!visited[p.first]) DFSUtil(p.first, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Dijkstra - O((V+E) log V)
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, 
                       greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& p : adj[u]) {
                int v = p.first, w = p.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // Detect cycle (undirected) - O(V + E)
    bool hasCycleUtil(int u, vector<bool>& visited, int parent) {
        visited[u] = true;
        for (auto& p : adj[u]) {
            if (!visited[p.first]) {
                if (hasCycleUtil(p.first, visited, u)) return true;
            } else if (p.first != parent) return true;
        }
        return false;
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i] && hasCycleUtil(i, visited, -1)) return true;
        }
        return false;
    }

    // Topological Sort (DAG) - O(V + E)
    void topoSortUtil(int u, vector<bool>& visited, stack<int>& st) {
        visited[u] = true;
        for (auto& p : adj[u]) {
            if (!visited[p.first]) topoSortUtil(p.first, visited, st);
        }
        st.push(u);
    }

    void topologicalSort() {
        vector<bool> visited(V, false);
        stack<int> st;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) topoSortUtil(i, visited, st);
        }
        cout << "Topological Sort: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }

    // Check bipartite - O(V + E)
    bool isBipartite() {
        vector<int> color(V, -1);
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (auto& p : adj[u]) {
                        if (color[p.first] == -1) {
                            color[p.first] = 1 - color[u];
                            q.push(p.first);
                        } else if (color[p.first] == color[u]) return false;
                    }
                }
            }
        }
        return true;
    }
};
```

## Example Usage

```cpp
int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    g.BFS(0);  // 0 1 2 3 4 5
    g.DFS(0);  // 0 1 3 2 4 5

    cout << "Has cycle: " << g.hasCycle() << endl;  // 1
    cout << "Is bipartite: " << g.isBipartite() << endl;

    // Weighted graph with Dijkstra
    Graph g2(5, true);
    g2.addEdge(0, 1, 4);
    g2.addEdge(0, 2, 1);
    g2.addEdge(2, 1, 2);
    g2.addEdge(1, 3, 1);
    g2.addEdge(2, 3, 5);
    g2.addEdge(3, 4, 3);

    vector<int> dist = g2.dijkstra(0);
    cout << "Dijkstra from 0: ";
    for (int i = 0; i < 5; i++) cout << dist[i] << " ";  // 0 3 1 4 7

    // DAG Topological Sort
    Graph g3(6, true);
    g3.addEdge(5, 2);
    g3.addEdge(5, 0);
    g3.addEdge(4, 0);
    g3.addEdge(4, 1);
    g3.addEdge(2, 3);
    g3.addEdge(3, 1);
    g3.topologicalSort();  // 5 4 2 3 1 0

    return 0;
}
```
