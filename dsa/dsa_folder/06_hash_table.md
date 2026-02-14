# Hash Table / HashMap

Key-value storage with O(1) average access time.

## Time Complexity

| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Contains | O(1) | O(n) |

## Hash Table with Chaining

```cpp
#include <iostream>
#include <list>
using namespace std;

class HashTable {
private:
    int capacity;
    list<pair<int, int>>* table;
    int count;

    int hash(int key) { return key % capacity; }

public:
    HashTable(int cap = 10) {
        capacity = cap;
        table = new list<pair<int, int>>[capacity];
        count = 0;
    }

    // Insert - O(1) average
    void insert(int key, int value) {
        int index = hash(key);
        for (auto& p : table[index]) {
            if (p.first == key) {
                p.second = value;  // Update
                return;
            }
        }
        table[index].push_back({key, value});
        count++;
    }

    // Search - O(1) average
    int get(int key) {
        int index = hash(key);
        for (auto& p : table[index]) {
            if (p.first == key) return p.second;
        }
        return -1;
    }

    // Delete - O(1) average
    void remove(int key) {
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if (it->first == key) {
                table[index].erase(it);
                count--;
                return;
            }
        }
    }

    // Contains - O(1) average
    bool contains(int key) {
        int index = hash(key);
        for (auto& p : table[index]) {
            if (p.first == key) return true;
        }
        return false;
    }

    int size() { return count; }
    bool isEmpty() { return count == 0; }
};
```

## HashSet

```cpp
class HashSet {
private:
    int capacity;
    list<int>* table;
    int count;

    int hash(int key) { return key % capacity; }

public:
    HashSet(int cap = 10) {
        capacity = cap;
        table = new list<int>[capacity];
        count = 0;
    }

    void add(int key) {
        if (contains(key)) return;
        int index = hash(key);
        table[index].push_back(key);
        count++;
    }

    void remove(int key) {
        int index = hash(key);
        table[index].remove(key);
        count--;
    }

    bool contains(int key) {
        int index = hash(key);
        for (int val : table[index]) {
            if (val == key) return true;
        }
        return false;
    }

    int size() { return count; }
};
```

## Example Usage

```cpp
int main() {
    // Hash Table
    HashTable ht;
    ht.insert(1, 100);
    ht.insert(11, 200);  // Same bucket as 1
    ht.insert(2, 300);

    cout << "Get key 11: " << ht.get(11) << endl;  // 200
    cout << "Contains 2: " << ht.contains(2) << endl;  // true

    ht.remove(11);
    cout << "Get key 11: " << ht.get(11) << endl;  // -1

    // Hash Set
    HashSet hs;
    hs.add(5);
    hs.add(10);
    hs.add(15);
    cout << "Contains 10: " << hs.contains(10) << endl;  // true
    hs.remove(10);
    cout << "Contains 10: " << hs.contains(10) << endl;  // false

    return 0;
}
```
