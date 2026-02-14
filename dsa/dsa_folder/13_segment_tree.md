# Segment Tree

A tree for efficient range queries and updates.

## Time Complexity

| Operation | Time |
|-----------|------|
| Build | O(n) |
| Query | O(log n) |
| Point Update | O(log n) |
| Range Update | O(log n) |

## Segment Tree for Range Sum

```cpp
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2*node, start, mid, idx, val);
            else
                update(2*node+1, mid+1, end, idx, val);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;  // Out of range
        if (l <= start && end <= r) return tree[node];  // Complete overlap
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + 
               query(2*node+1, mid+1, end, l, r);
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n-1);
    }

    void update(int idx, int val) { update(1, 0, n-1, idx, val); }
    int query(int l, int r) { return query(1, 0, n-1, l, r); }
};
```

## Segment Tree for Range Min

```cpp
class MinSegmentTree {
private:
    vector<int> tree;
    int n;

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = min(tree[2*node], tree[2*node+1]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INT_MAX;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return min(query(2*node, start, mid, l, r),
                   query(2*node+1, mid+1, end, l, r));
    }

public:
    MinSegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n-1);
    }

    int query(int l, int r) { return query(1, 0, n-1, l, r); }
};
```

## Lazy Propagation (Range Update)

```cpp
class LazySegmentTree {
private:
    vector<long long> tree, lazy;
    int n;

    void pushDown(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void rangeUpdate(int node, int start, int end, int l, int r, int val) {
        pushDown(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] += val;
            pushDown(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        rangeUpdate(2*node, start, mid, l, r, val);
        rangeUpdate(2*node+1, mid+1, end, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    long long query(int node, int start, int end, int l, int r) {
        pushDown(node, start, end);
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + 
               query(2*node+1, mid+1, end, l, r);
    }

public:
    LazySegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void rangeUpdate(int l, int r, int val) { rangeUpdate(1, 0, n-1, l, r, val); }
    long long query(int l, int r) { return query(1, 0, n-1, l, r); }
};
```

## Example Usage

```cpp
int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << "Sum [1,3]: " << st.query(1, 3) << endl;  // 15
    cout << "Sum [0,5]: " << st.query(0, 5) << endl;  // 36

    st.update(2, 10);  // arr[2] = 10
    cout << "After update, Sum [1,3]: " << st.query(1, 3) << endl;  // 20

    // Lazy Segment Tree
    LazySegmentTree lst(6);
    lst.rangeUpdate(0, 5, 5);  // Add 5 to all
    cout << "Sum [0,5]: " << lst.query(0, 5) << endl;  // 30

    lst.rangeUpdate(2, 4, 3);  // Add 3 to [2,4]
    cout << "Sum [0,5]: " << lst.query(0, 5) << endl;  // 39

    return 0;
}
```
