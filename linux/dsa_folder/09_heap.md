# Heap (Min/Max)

A complete binary tree where parent is greater (max) or smaller (min) than children.

## Time Complexity

| Operation | Time |
|-----------|------|
| Insert | O(log n) |
| Extract Min/Max | O(log n) |
| Peek | O(1) |
| Build Heap | O(n) |
| Heapify | O(log n) |

## Max Heap Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;
        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Insert - O(log n)
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    // Extract Max - O(log n)
    int extractMax() {
        if (heap.empty()) return -1;
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return maxVal;
    }

    // Peek - O(1)
    int getMax() { return heap.empty() ? -1 : heap[0]; }

    // Increase key - O(log n)
    void increaseKey(int i, int newVal) {
        if (newVal < heap[i]) return;
        heap[i] = newVal;
        heapifyUp(i);
    }

    int size() { return heap.size(); }
    bool isEmpty() { return heap.empty(); }
};
```

## Min Heap Implementation

```cpp
class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) return -1;
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return minVal;
    }

    int getMin() { return heap.empty() ? -1 : heap[0]; }
};
```

## Heap Sort - O(n log n)

```cpp
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        // heapify
        int j = i;
        while (true) {
            int largest = j;
            int left = 2 * j + 1;
            int right = 2 * j + 2;
            if (left < n && arr[left] > arr[largest]) largest = left;
            if (right < n && arr[right] > arr[largest]) largest = right;
            if (largest == j) break;
            swap(arr[j], arr[largest]);
            j = largest;
        }
    }
    
    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        // heapify on reduced heap
        int j = 0;
        while (true) {
            int largest = j;
            int left = 2 * j + 1;
            int right = 2 * j + 2;
            if (left < i && arr[left] > arr[largest]) largest = left;
            if (right < i && arr[right] > arr[largest]) largest = right;
            if (largest == j) break;
            swap(arr[j], arr[largest]);
            j = largest;
        }
    }
}
```

## Example Usage

```cpp
int main() {
    MaxHeap maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);

    cout << "Max: " << maxHeap.getMax() << endl;  // 30
    cout << "Extract: " << maxHeap.extractMax() << endl;  // 30
    cout << "Max: " << maxHeap.getMax() << endl;  // 20

    MinHeap minHeap;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);

    cout << "Min: " << minHeap.getMin() << endl;  // 5
    cout << "Extract: " << minHeap.extractMin() << endl;  // 5

    // Heap Sort
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    heapSort(arr);  // 5 6 7 11 12 13

    return 0;
}
```
