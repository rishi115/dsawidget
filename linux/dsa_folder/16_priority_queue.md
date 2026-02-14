# Priority Queue

A queue where elements are dequeued based on priority.

## Time Complexity

| Operation | Time |
|-----------|------|
| Insert | O(log n) |
| Extract Max/Min | O(log n) |
| Peek | O(1) |

## Custom Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<typename T, typename Compare = less<T>>
class PriorityQueue {
private:
    vector<T> heap;
    Compare comp;

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (comp(heap[parent], heap[i])) {
                swap(heap[parent], heap[i]);
                i = parent;
            } else break;
        }
    }

    void heapifyDown(int i) {
        int n = heap.size();
        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && comp(heap[largest], heap[left]))
                largest = left;
            if (right < n && comp(heap[largest], heap[right]))
                largest = right;

            if (largest != i) {
                swap(heap[i], heap[largest]);
                i = largest;
            } else break;
        }
    }

public:
    void push(T val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
    }

    T top() { return heap[0]; }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};
```

## Applications

### Kth Largest Element

```cpp
int kthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}
```

### Merge K Sorted Arrays

```cpp
vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    priority_queue<pair<int, pair<int,int>>, 
                   vector<pair<int, pair<int,int>>>,
                   greater<pair<int, pair<int,int>>>> pq;

    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            pq.push({arrays[i][0], {i, 0}});
        }
    }

    vector<int> result;
    while (!pq.empty()) {
        auto [val, pos] = pq.top();
        pq.pop();
        result.push_back(val);

        int arrIdx = pos.first;
        int elemIdx = pos.second;
        if (elemIdx + 1 < arrays[arrIdx].size()) {
            pq.push({arrays[arrIdx][elemIdx + 1], {arrIdx, elemIdx + 1}});
        }
    }
    return result;
}
```

## Example Usage

```cpp
int main() {
    // Max Priority Queue (default)
    PriorityQueue<int> maxPQ;
    maxPQ.push(10);
    maxPQ.push(30);
    maxPQ.push(20);

    cout << "Max PQ: ";
    while (!maxPQ.empty()) {
        cout << maxPQ.top() << " ";  // 30 20 10
        maxPQ.pop();
    }
    cout << endl;

    // Min Priority Queue (STL)
    priority_queue<int, vector<int>, greater<int>> minPQ;
    minPQ.push(10);
    minPQ.push(30);
    minPQ.push(20);

    cout << "Min PQ: ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";  // 10 20 30
        minPQ.pop();
    }
    cout << endl;

    // Kth Largest
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "3rd largest: " << kthLargest(nums, 3) << endl;  // 4

    // Merge K Sorted
    vector<vector<int>> arrays = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    vector<int> merged = mergeKSorted(arrays);
    cout << "Merged: ";
    for (int x : merged) cout << x << " ";  // 1 2 3 4 5 6 7 8 9

    return 0;
}
```
