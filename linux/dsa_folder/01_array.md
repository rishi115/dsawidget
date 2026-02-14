# Array

Dynamic array implementation with all operations.

## Time Complexity

| Operation | Time |
|-----------|------|
| Access | O(1) |
| Update | O(1) |
| Insert (end) | O(1) amortized |
| Insert (middle) | O(n) |
| Delete (end) | O(1) |
| Delete (middle) | O(n) |
| Search | O(n) |
| Binary Search | O(log n) |

## Implementation

```cpp
#include <iostream>
using namespace std;

class Array {
private:
    int* arr;
    int capacity;
    int size;

public:
    // Constructor
    Array(int cap = 10) {
        capacity = cap;
        arr = new int[capacity];
        size = 0;
    }

    // Destructor
    ~Array() {
        delete[] arr;
    }

    // Access element by index - O(1)
    int get(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds\n";
            return -1;
        }
        return arr[index];
    }

    // Update element at index - O(1)
    void set(int index, int value) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds\n";
            return;
        }
        arr[index] = value;
    }

    // Insert at end - O(1) amortized
    void pushBack(int value) {
        if (size == capacity) {
            resize();
        }
        arr[size++] = value;
    }

    // Insert at index - O(n)
    void insertAt(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Invalid index\n";
            return;
        }
        if (size == capacity) {
            resize();
        }
        // Shift elements to right
        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        size++;
    }

    // Delete from end - O(1)
    void popBack() {
        if (size == 0) {
            cout << "Array is empty\n";
            return;
        }
        size--;
    }

    // Delete at index - O(n)
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds\n";
            return;
        }
        // Shift elements to left
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    // Linear Search - O(n)
    int search(int value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // Binary Search (for sorted array) - O(log n)
    int binarySearch(int value) {
        int left = 0, right = size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == value) return mid;
            if (arr[mid] < value) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    // Resize array - O(n)
    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

    // Reverse array - O(n)
    void reverse() {
        int left = 0, right = size - 1;
        while (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    // Get size - O(1)
    int getSize() { return size; }

    // Check if empty - O(1)
    bool isEmpty() { return size == 0; }

    // Print array
    void print() {
        cout << "Array: [";
        for (int i = 0; i < size; i++) {
            cout << arr[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]\n";
    }
};
```

## Example Usage

```cpp
int main() {
    Array arr(5);

    arr.pushBack(10);
    arr.pushBack(20);
    arr.pushBack(30);
    arr.pushBack(40);
    arr.print();  // [10, 20, 30, 40]

    cout << "Element at index 2: " << arr.get(2) << endl;  // 30

    arr.set(2, 35);
    arr.print();  // [10, 20, 35, 40]

    arr.insertAt(1, 15);
    arr.print();  // [10, 15, 20, 35, 40]

    arr.deleteAt(2);
    arr.print();  // [10, 15, 35, 40]

    cout << "Index of 35: " << arr.search(35) << endl;  // 2

    arr.reverse();
    arr.print();  // [40, 35, 15, 10]

    return 0;
}
```
