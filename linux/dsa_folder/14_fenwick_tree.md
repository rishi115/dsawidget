# Fenwick Tree (Binary Indexed Tree)

A data structure for efficient prefix sum queries and point updates.

## Time Complexity

| Operation | Time |
|-----------|------|
| Build | O(n log n) |
| Point Update | O(log n) |
| Prefix Sum | O(log n) |
| Range Sum | O(log n) |

## Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size) {
        n = size;
        tree.resize(n + 1, 0);
    }

    // Build from array - O(n log n)
    FenwickTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }

    // Point update: add delta to index i - O(log n)
    void update(int i, int delta) {
        i++;  // 1-indexed
        while (i <= n) {
            tree[i] += delta;
            i += i & (-i);  // Add LSB
        }
    }

    // Prefix sum [0, i] - O(log n)
    int prefixSum(int i) {
        i++;  // 1-indexed
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);  // Remove LSB
        }
        return sum;
    }

    // Range sum [l, r] - O(log n)
    int rangeSum(int l, int r) {
        if (l == 0) return prefixSum(r);
        return prefixSum(r) - prefixSum(l - 1);
    }

    // Get single element value - O(log n)
    int get(int i) {
        return rangeSum(i, i);
    }

    // Set element to specific value - O(log n)
    void set(int i, int val) {
        int current = get(i);
        update(i, val - current);
    }
};
```

## 2D Fenwick Tree

```cpp
class FenwickTree2D {
private:
    vector<vector<int>> tree;
    int rows, cols;

public:
    FenwickTree2D(int r, int c) {
        rows = r;
        cols = c;
        tree.resize(rows + 1, vector<int>(cols + 1, 0));
    }

    void update(int x, int y, int delta) {
        x++; y++;
        for (int i = x; i <= rows; i += i & (-i)) {
            for (int j = y; j <= cols; j += j & (-j)) {
                tree[i][j] += delta;
            }
        }
    }

    int prefixSum(int x, int y) {
        x++; y++;
        int sum = 0;
        for (int i = x; i > 0; i -= i & (-i)) {
            for (int j = y; j > 0; j -= j & (-j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // Sum of rectangle from (x1,y1) to (x2,y2)
    int rangeSum(int x1, int y1, int x2, int y2) {
        int sum = prefixSum(x2, y2);
        if (x1 > 0) sum -= prefixSum(x1 - 1, y2);
        if (y1 > 0) sum -= prefixSum(x2, y1 - 1);
        if (x1 > 0 && y1 > 0) sum += prefixSum(x1 - 1, y1 - 1);
        return sum;
    }
};
```

## Example Usage

```cpp
int main() {
    // 1D Fenwick Tree
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    FenwickTree ft(arr);

    cout << "Prefix sum [0,3]: " << ft.prefixSum(3) << endl;  // 16
    cout << "Range sum [2,4]: " << ft.rangeSum(2, 4) << endl;  // 21

    ft.update(2, 5);  // Add 5 to arr[2]
    cout << "After adding 5 to arr[2]:\n";
    cout << "Range sum [2,4]: " << ft.rangeSum(2, 4) << endl;  // 26

    ft.set(2, 3);  // Set arr[2] = 3
    cout << "After setting arr[2]=3:\n";
    cout << "Range sum [2,4]: " << ft.rangeSum(2, 4) << endl;  // 19

    // 2D Fenwick Tree
    FenwickTree2D ft2d(4, 4);
    ft2d.update(0, 0, 1);
    ft2d.update(0, 1, 2);
    ft2d.update(1, 0, 3);
    ft2d.update(1, 1, 4);

    cout << "\n2D Fenwick Tree:\n";
    cout << "Sum (0,0) to (1,1): " << ft2d.rangeSum(0, 0, 1, 1) << endl;  // 10

    return 0;
}
```
