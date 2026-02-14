#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

// Hash Table with Chaining
class HashTable {
private:
    int capacity;
    list<pair<int, int>>* table;  // key-value pairs
    int count;

    int hash(int key) {
        return key % capacity;
    }

public:
    HashTable(int cap = 10) {
        capacity = cap;
        table = new list<pair<int, int>>[capacity];
        count = 0;
    }

    ~HashTable() { delete[] table; }

    // Insert - O(1) average
    void insert(int key, int value) {
        int index = hash(key);
        for (auto& p : table[index]) {
            if (p.first == key) {
                p.second = value;  // Update existing
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
        return -1;  // Not found
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

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            for (auto& p : table[i]) {
                cout << "[" << p.first << "," << p.second << "] ";
            }
            cout << endl;
        }
    }
};

// HashSet
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

int main() {
    cout << "=== Hash Table ===\n";
    HashTable ht;
    ht.insert(1, 100);
    ht.insert(11, 200);  // Same bucket as 1
    ht.insert(2, 300);
    ht.insert(21, 400);
    ht.print();

    cout << "Get key 11: " << ht.get(11) << endl;
    cout << "Contains 2: " << (ht.contains(2) ? "Yes" : "No") << endl;

    ht.remove(11);
    cout << "After removing 11:\n";
    ht.print();

    cout << "\n=== Hash Set ===\n";
    HashSet hs;
    hs.add(5);
    hs.add(10);
    hs.add(15);
    cout << "Contains 10: " << (hs.contains(10) ? "Yes" : "No") << endl;
    hs.remove(10);
    cout << "After remove, contains 10: " << (hs.contains(10) ? "Yes" : "No") << endl;

    return 0;
}
