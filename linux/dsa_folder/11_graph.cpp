#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <climits>
#include <algorithm>
using namespace std;

// Graph using Adjacency List
class Graph {
private:
    int V;  // Number of vertices
    vector<list<pair<int, int>>> adj;  // {neighbor, weight}
    bool directed;

public:
    Graph(int vertices, bool isDirected = false) {
        V = vertices;
        adj.resize(V);
        directed = isDirected;
    }

    // Add edge - O(1)
    void addEdge(int u, int v, int weight = 1) {
        adj[u].push_back({v, weight});
        if (!directed) {
            adj[v].push_back({u, weight});
        }
    }

    // Remove edge - O(E)
    void removeEdge(int u, int v) {
        adj[u].remove_if([v](pair<int,int>& p) { return p.first == v; });
        if (!directed) {
            adj[v].remove_if([u](pair<int,int>& p) { return p.first == u; });
        }
    }

    // Check if edge exists - O(V)
    bool hasEdge(int u, int v) {
        for (auto& p : adj[u]) {
            if (p.first == v) return true;
        }
        return false;
    }

    // Get neighbors - O(1)
    vector<int> getNeighbors(int u) {
        vector<int> neighbors;
        for (auto& p : adj[u]) {
            neighbors.push_back(p.first);
        }
        return neighbors;
    }

    // BFS - O(V + E)
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS: ";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
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
            if (!visited[p.first]) {
                DFSUtil(p.first, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // DFS Iterative
    void DFSIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);

        cout << "DFS Iterative: ";
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            if (!visited[u]) {
                visited[u] = true;
                cout << u << " ";
                for (auto& p : adj[u]) {
                    if (!visited[p.first]) {
                        s.push(p.first);
                    }
                }
            }
        }
        cout << endl;
    }

    // Dijkstra's Algorithm - O((V+E) log V)
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& p : adj[u]) {
                int v = p.first;
                int w = p.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // Detect cycle in undirected graph - O(V + E)
    bool hasCycleUndirected() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (hasCycleUtil(i, visited, -1)) return true;
            }
        }
        return false;
    }

    bool hasCycleUtil(int u, vector<bool>& visited, int parent) {
        visited[u] = true;
        for (auto& p : adj[u]) {
            if (!visited[p.first]) {
                if (hasCycleUtil(p.first, visited, u)) return true;
            } else if (p.first != parent) {
                return true;
            }
        }
        return false;
    }

    // Topological Sort (for DAG) - O(V + E)
    void topologicalSortUtil(int u, vector<bool>& visited, stack<int>& st) {
        visited[u] = true;
        for (auto& p : adj[u]) {
            if (!visited[p.first]) {
                topologicalSortUtil(p.first, visited, st);
            }
        }
        st.push(u);
    }

    void topologicalSort() {
        vector<bool> visited(V, false);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, st);
            }
        }

        cout << "Topological Sort: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }

    // Shortest path in unweighted graph - O(V + E)
    vector<int> shortestPath(int src) {
        vector<int> dist(V, INT_MAX);
        queue<int> q;
        dist[src] = 0;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& p : adj[u]) {
                if (dist[p.first] == INT_MAX) {
                    dist[p.first] = dist[u] + 1;
                    q.push(p.first);
                }
            }
        }
        return dist;
    }

    // Count connected components - O(V + E)
    int countComponents() {
        vector<bool> visited(V, false);
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited);
                count++;
            }
        }
        return count;
    }

    // Check if graph is bipartite - O(V + E)
    bool isBipartite() {
        vector<int> color(V, -1);
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (auto& p : adj[u]) {
                        if (color[p.first] == -1) {
                            color[p.first] = 1 - color[u];
                            q.push(p.first);
                        } else if (color[p.first] == color[u]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    void print() {
        cout << "Graph:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (auto& p : adj[i]) {
                cout << "(" << p.first << "," << p.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== Undirected Graph ===\n";
    Graph g1(6);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    g1.print();

    g1.BFS(0);
    g1.DFS(0);
    g1.DFSIterative(0);

    cout << "Has cycle: " << (g1.hasCycleUndirected() ? "Yes" : "No") << endl;
    cout << "Is bipartite: " << (g1.isBipartite() ? "Yes" : "No") << endl;

    cout << "\n=== Directed Weighted Graph ===\n";
    Graph g2(5, true);
    g2.addEdge(0, 1, 4);
    g2.addEdge(0, 2, 1);
    g2.addEdge(2, 1, 2);
    g2.addEdge(1, 3, 1);
    g2.addEdge(2, 3, 5);
    g2.addEdge(3, 4, 3);
    g2.print();

    vector<int> dist = g2.dijkstra(0);
    cout << "Dijkstra from 0: ";
    for (int i = 0; i < 5; i++) {
        cout << "to " << i << "=" << dist[i] << " ";
    }
    cout << endl;

    cout << "\n=== DAG Topological Sort ===\n";
    Graph g3(6, true);
    g3.addEdge(5, 2);
    g3.addEdge(5, 0);
    g3.addEdge(4, 0);
    g3.addEdge(4, 1);
    g3.addEdge(2, 3);
    g3.addEdge(3, 1);
    g3.topologicalSort();

    return 0;
}
