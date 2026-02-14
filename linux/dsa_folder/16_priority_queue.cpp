#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

// Custom Priority Queue using Heap
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
    // Insert - O(log n)
    void push(T val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    // Remove top - O(log n)
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
    }

    // Get top - O(1)
    T top() { return heap[0]; }

    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

// Applications of Priority Queue

// 1. Kth Largest Element
int kthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

// 2. Merge K Sorted Arrays
vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    priority_queue<pair<int, pair<int,int>>, 
                   vector<pair<int, pair<int,int>>>,
                   greater<pair<int, pair<int,int>>>> pq;

    // Push first element of each array
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

// 3. Task Scheduler (simplified)
int taskScheduler(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char c : tasks) freq[c - 'A']++;

    priority_queue<int> pq;
    for (int f : freq) if (f > 0) pq.push(f);

    int time = 0;
    while (!pq.empty()) {
        vector<int> temp;
        for (int i = 0; i <= n; i++) {
            if (!pq.empty()) {
                temp.push_back(pq.top() - 1);
                pq.pop();
            }
            time++;
            if (pq.empty() && temp.empty()) break;
        }
        for (int t : temp) if (t > 0) pq.push(t);
    }
    return time;
}

int main() {
    cout << "=== Custom Priority Queue (Max) ===\n";
    PriorityQueue<int> maxPQ;
    maxPQ.push(10);
    maxPQ.push(30);
    maxPQ.push(20);
    maxPQ.push(5);

    cout << "Elements (max first): ";
    while (!maxPQ.empty()) {
        cout << maxPQ.top() << " ";
        maxPQ.pop();
    }
    cout << endl;  // 30 20 10 5

    cout << "\n=== STL Priority Queue (Min) ===\n";
    priority_queue<int, vector<int>, greater<int>> minPQ;
    minPQ.push(10);
    minPQ.push(30);
    minPQ.push(20);
    minPQ.push(5);

    cout << "Elements (min first): ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << endl;  // 5 10 20 30

    cout << "\n=== Kth Largest Element ===\n";
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "3rd largest in [3,2,1,5,6,4]: " << kthLargest(nums, 3) << endl;  // 4

    cout << "\n=== Merge K Sorted Arrays ===\n";
    vector<vector<int>> arrays = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    vector<int> merged = mergeKSorted(arrays);
    cout << "Merged: ";
    for (int x : merged) cout << x << " ";
    cout << endl;  // 1 2 3 4 5 6 7 8 9

    return 0;
}
