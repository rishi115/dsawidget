# Disjoint Set Union (Union-Find)

A data structure to track elements partitioned into disjoint sets.

## Time Complexity

| Operation | Time |
|-----------|------|
| MakeSet | O(1) |
| Find | O(α(n)) ≈ O(1) |
| Union | O(α(n)) ≈ O(1) |
| Connected | O(α(n)) ≈ O(1) |

*α(n) is the inverse Ackermann function, practically constant*

## Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank_;
    int components;

public:
    DSU(int n) {
        parent.resize(n);
        rank_.resize(n, 0);
        components = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Each element is its own parent
        }
    }

    // Find with path compression - O(α(n))
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    // Union by rank - O(α(n))
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        if (rank_[rootX] < rank_[rootY]) {
            parent[rootX] = rootY;
        } else if (rank_[rootX] > rank_[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank_[rootX]++;
        }
        components--;
    }

    // Check if connected - O(α(n))
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponents() { return components; }
};
```

## Kruskal's MST using DSU

```cpp
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(V);
    int mstWeight = 0;
    int edgesUsed = 0;

    cout << "MST Edges: ";
    for (Edge& e : edges) {
        if (!dsu.connected(e.u, e.v)) {
            dsu.unite(e.u, e.v);
            mstWeight += e.weight;
            edgesUsed++;
            cout << "(" << e.u << "-" << e.v << ") ";
            if (edgesUsed == V - 1) break;
        }
    }
    cout << endl;
    return mstWeight;
}
```

## Cycle Detection using DSU

```cpp
bool hasCycle(int V, vector<pair<int,int>>& edges) {
    DSU dsu(V);
    for (auto& e : edges) {
        if (dsu.connected(e.first, e.second)) {
            return true;  // Cycle detected
        }
        dsu.unite(e.first, e.second);
    }
    return false;
}
```

## Example Usage

```cpp
int main() {
    DSU dsu(7);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(5, 6);
    dsu.unite(4, 5);

    cout << "0 and 2 connected: " << dsu.connected(0, 2) << endl;  // 1
    cout << "0 and 3 connected: " << dsu.connected(0, 3) << endl;  // 0
    cout << "3 and 6 connected: " << dsu.connected(3, 6) << endl;  // 1
    cout << "Components: " << dsu.getComponents() << endl;  // 2

    dsu.unite(2, 3);
    cout << "After uniting 2 and 3:\n";
    cout << "0 and 6 connected: " << dsu.connected(0, 6) << endl;  // 1
    cout << "Components: " << dsu.getComponents() << endl;  // 1

    // Kruskal's MST
    vector<Edge> edges = {
        {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11},
        {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9},
        {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7}
    };
    int mstWeight = kruskalMST(9, edges);
    cout << "MST Weight: " << mstWeight << endl;  // 37

    // Cycle Detection
    vector<pair<int,int>> graphEdges1 = {{0, 1}, {1, 2}, {2, 0}};
    cout << "Graph 1 has cycle: " << hasCycle(3, graphEdges1) << endl;  // 1

    vector<pair<int,int>> graphEdges2 = {{0, 1}, {1, 2}, {2, 3}};
    cout << "Graph 2 has cycle: " << hasCycle(4, graphEdges2) << endl;  // 0

    return 0;
}
```
