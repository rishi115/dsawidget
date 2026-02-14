# LRU Cache

Least Recently Used cache with O(1) get and put operations.

## Time Complexity

| Operation | Time |
|-----------|------|
| Get | O(1) |
| Put | O(1) |
| Delete | O(1) |

## LRU Cache Implementation

```cpp
#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;  // {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> map;

public:
    LRUCache(int cap) : capacity(cap) {}

    // Get - O(1)
    int get(int key) {
        if (map.find(key) == map.end()) return -1;

        // Move to front (most recently used)
        auto it = map[key];
        int value = it->second;
        cache.erase(it);
        cache.push_front({key, value});
        map[key] = cache.begin();

        return value;
    }

    // Put - O(1)
    void put(int key, int value) {
        // If key exists, update and move to front
        if (map.find(key) != map.end()) {
            cache.erase(map[key]);
        }
        // If at capacity, remove LRU (back)
        else if (cache.size() >= capacity) {
            int lruKey = cache.back().first;
            cache.pop_back();
            map.erase(lruKey);
        }

        // Add to front
        cache.push_front({key, value});
        map[key] = cache.begin();
    }

    void print() {
        cout << "Cache (MRU -> LRU): ";
        for (auto& p : cache) {
            cout << "[" << p.first << ":" << p.second << "] ";
        }
        cout << endl;
    }
};
```

## LFU Cache Implementation

```cpp
class LFUCache {
private:
    int capacity;
    int minFreq;
    unordered_map<int, pair<int, int>> keyToValFreq;  // key -> {value, freq}
    unordered_map<int, list<int>> freqToKeys;  // freq -> list of keys
    unordered_map<int, list<int>::iterator> keyToIter;

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (keyToValFreq.find(key) == keyToValFreq.end()) return -1;

        int value = keyToValFreq[key].first;
        int freq = keyToValFreq[key].second;

        // Update frequency
        freqToKeys[freq].erase(keyToIter[key]);
        if (freqToKeys[freq].empty()) {
            freqToKeys.erase(freq);
            if (minFreq == freq) minFreq++;
        }

        freq++;
        keyToValFreq[key].second = freq;
        freqToKeys[freq].push_front(key);
        keyToIter[key] = freqToKeys[freq].begin();

        return value;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        if (keyToValFreq.find(key) != keyToValFreq.end()) {
            keyToValFreq[key].first = value;
            get(key);  // Update frequency
            return;
        }

        if (keyToValFreq.size() >= capacity) {
            // Remove LFU key
            int lfuKey = freqToKeys[minFreq].back();
            freqToKeys[minFreq].pop_back();
            if (freqToKeys[minFreq].empty()) {
                freqToKeys.erase(minFreq);
            }
            keyToValFreq.erase(lfuKey);
            keyToIter.erase(lfuKey);
        }

        // Add new key
        keyToValFreq[key] = {value, 1};
        freqToKeys[1].push_front(key);
        keyToIter[key] = freqToKeys[1].begin();
        minFreq = 1;
    }
};
```

## Example Usage

```cpp
int main() {
    // LRU Cache
    LRUCache lru(3);

    lru.put(1, 100);
    lru.put(2, 200);
    lru.put(3, 300);
    lru.print();  // [3:300] [2:200] [1:100]

    cout << "Get 1: " << lru.get(1) << endl;  // 100
    lru.print();  // [1:100] [3:300] [2:200]

    lru.put(4, 400);  // Evicts key 2
    lru.print();  // [4:400] [1:100] [3:300]

    cout << "Get 2: " << lru.get(2) << endl;  // -1 (evicted)

    // LFU Cache
    LFUCache lfu(2);

    lfu.put(1, 10);
    lfu.put(2, 20);
    cout << "Get 1: " << lfu.get(1) << endl;  // 10, freq of 1 becomes 2

    lfu.put(3, 30);  // Evicts key 2 (freq=1)
    cout << "Get 2: " << lfu.get(2) << endl;  // -1 (evicted)
    cout << "Get 3: " << lfu.get(3) << endl;  // 30

    return 0;
}
```
