#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1. Bubble Sort - O(n²)
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // Optimization
    }
}

// 2. Selection Sort - O(n²)
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// 3. Insertion Sort - O(n²)
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort - O(n log n)
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 5. Quick Sort - O(n log n) avg, O(n²) worst
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. Counting Sort - O(n + k)
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    for (int num : arr) count[num - minVal]++;

    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (count[i]-- > 0) arr[idx++] = i + minVal;
    }
}

// 7. Radix Sort - O(d * (n + k))
void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    for (int num : arr) count[(num / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    arr = output;
}

void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

// 8. Heap Sort - O(n log n)
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(vector<int>& arr, string name) {
    cout << name << ": ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(arr1);
    printArray(arr1, "Bubble Sort");

    vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
    selectionSort(arr2);
    printArray(arr2, "Selection Sort");

    vector<int> arr3 = {64, 34, 25, 12, 22, 11, 90};
    insertionSort(arr3);
    printArray(arr3, "Insertion Sort");

    vector<int> arr4 = {64, 34, 25, 12, 22, 11, 90};
    mergeSort(arr4, 0, arr4.size() - 1);
    printArray(arr4, "Merge Sort");

    vector<int> arr5 = {64, 34, 25, 12, 22, 11, 90};
    quickSort(arr5, 0, arr5.size() - 1);
    printArray(arr5, "Quick Sort");

    vector<int> arr6 = {64, 34, 25, 12, 22, 11, 90};
    countingSort(arr6);
    printArray(arr6, "Counting Sort");

    vector<int> arr7 = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(arr7);
    printArray(arr7, "Radix Sort");

    vector<int> arr8 = {64, 34, 25, 12, 22, 11, 90};
    heapSort(arr8);
    printArray(arr8, "Heap Sort");

    return 0;
}
