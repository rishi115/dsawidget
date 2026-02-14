# Searching Algorithms

All major searching algorithms with implementations.

## Time Complexity

| Algorithm | Time | Space |
|-----------|------|-------|
| Linear Search | O(n) | O(1) |
| Binary Search | O(log n) | O(1) |
| Lower Bound | O(log n) | O(1) |
| Upper Bound | O(log n) | O(1) |

## 1. Linear Search

```cpp
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

## 2. Binary Search

```cpp
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

## 3. Binary Search (Recursive)

```cpp
int binarySearchRecursive(vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) 
        return binarySearchRecursive(arr, target, mid + 1, right);
    return binarySearchRecursive(arr, target, left, mid - 1);
}
```

## 4. Lower Bound (First element >= target)

```cpp
int lowerBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}
```

## 5. Upper Bound (First element > target)

```cpp
int upperBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) left = mid + 1;
        else right = mid;
    }
    return left;
}
```

## 6. Find First and Last Position

```cpp
pair<int, int> searchRange(vector<int>& arr, int target) {
    int first = lowerBound(arr, target);
    if (first == arr.size() || arr[first] != target) return {-1, -1};
    int last = upperBound(arr, target) - 1;
    return {first, last};
}
```

## 7. Search in Rotated Sorted Array

```cpp
int searchRotated(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;

        if (arr[left] <= arr[mid]) {  // Left half sorted
            if (arr[left] <= target && target < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } else {  // Right half sorted
            if (arr[mid] < target && target <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}
```

## 8. Find Minimum in Rotated Sorted Array

```cpp
int findMin(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[right]) left = mid + 1;
        else right = mid;
    }
    return arr[left];
}
```

## 9. Peak Element

```cpp
int findPeakElement(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[mid + 1]) right = mid;
        else left = mid + 1;
    }
    return left;
}
```

## 10. Search in 2D Matrix

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = matrix[mid / n][mid % n];
        if (val == target) return true;
        if (val < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}
```

## 11. Square Root (Binary Search)

```cpp
int mySqrt(int x) {
    if (x < 2) return x;
    long left = 1, right = x / 2;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        if (mid * mid == x) return mid;
        if (mid * mid < x) left = mid + 1;
        else right = mid - 1;
    }
    return right;
}
```

## Example Usage

```cpp
int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};

    cout << "Linear Search 7: " << linearSearch(arr, 7) << endl;  // 3
    cout << "Binary Search 7: " << binarySearch(arr, 7) << endl;  // 3
    cout << "Lower Bound 6: " << lowerBound(arr, 6) << endl;      // 3
    cout << "Upper Bound 7: " << upperBound(arr, 7) << endl;      // 4

    vector<int> arr2 = {1, 2, 2, 2, 3, 4, 5};
    auto range = searchRange(arr2, 2);
    cout << "Range of 2: [" << range.first << ", " << range.second << "]\n";  // [1, 3]

    vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << "Search 0 in rotated: " << searchRotated(rotated, 0) << endl;  // 4
    cout << "Min in rotated: " << findMin(rotated) << endl;  // 0

    cout << "Sqrt(16): " << mySqrt(16) << endl;  // 4
    cout << "Sqrt(8): " << mySqrt(8) << endl;    // 2

    return 0;
}
```
