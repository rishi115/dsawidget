#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Max Heap
class MaxHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    // Heapify up - O(log n)
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    // Heapify down - O(log n)
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

    // Delete at index - O(log n)
    void deleteAt(int i) {
        increaseKey(i, INT_MAX);
        extractMax();
    }

    int size() { return heap.size(); }
    bool isEmpty() { return heap.empty(); }

    void print() {
        cout << "Heap: ";
        for (int val : heap) cout << val << " ";
        cout << endl;
    }
};

// Min Heap
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
    int size() { return heap.size(); }
    bool isEmpty() { return heap.empty(); }
};

// Build heap from array - O(n)
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;
        if (largest != i) swap(arr[i], arr[largest]);
    }
}

// Heap Sort - O(n log n)
void heapSort(vector<int>& arr) {
    int n = arr.size();
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
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

int main() {
    cout << "=== Max Heap ===\n";
    MaxHeap maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);
    maxHeap.insert(15);
    maxHeap.print();  // 30 20 5 10 15

    cout << "Max: " << maxHeap.getMax() << endl;  // 30
    cout << "Extract Max: " << maxHeap.extractMax() << endl;  // 30
    maxHeap.print();  // 20 15 5 10

    cout << "\n=== Min Heap ===\n";
    MinHeap minHeap;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);
    minHeap.insert(30);
    minHeap.insert(15);

    cout << "Min: " << minHeap.getMin() << endl;  // 5
    cout << "Extract Min: " << minHeap.extractMin() << endl;  // 5
    cout << "New Min: " << minHeap.getMin() << endl;  // 10

    cout << "\n=== Heap Sort ===\n";
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Before: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    heapSort(arr);
    cout << "After: ";
    for (int x : arr) cout << x << " ";
    cout << endl;  // 5 6 7 11 12 13

    return 0;
}
