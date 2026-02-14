# Trie (Prefix Tree)

A tree for storing strings where each node represents a character.

## Time Complexity

| Operation | Time |
|-----------|------|
| Insert | O(m) |
| Search | O(m) |
| StartsWith | O(m) |
| Delete | O(m) |
| AutoComplete | O(m + k) |

*m = word length, k = number of results*

## Implementation

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    int wordCount;

    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
        isEndOfWord = false;
        wordCount = 0;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    // Insert - O(m)
    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index]) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
        curr->wordCount++;
    }

    // Search exact word - O(m)
    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index]) return false;
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
    }

    // Check if prefix exists - O(m)
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!curr->children[index]) return false;
            curr = curr->children[index];
        }
        return true;
    }

    // Delete word - O(m)
    bool deleteWord(TrieNode* curr, string word, int depth) {
        if (!curr) return false;
        if (depth == word.size()) {
            if (!curr->isEndOfWord) return false;
            curr->isEndOfWord = false;
            curr->wordCount--;
            for (int i = 0; i < 26; i++) {
                if (curr->children[i]) return false;
            }
            return true;
        }
        int index = word[depth] - 'a';
        if (deleteWord(curr->children[index], word, depth + 1)) {
            delete curr->children[index];
            curr->children[index] = nullptr;
            if (!curr->isEndOfWord) {
                for (int i = 0; i < 26; i++) {
                    if (curr->children[i]) return false;
                }
                return true;
            }
        }
        return false;
    }

    void deleteWord(string word) {
        deleteWord(root, word, 0);
    }

    // Autocomplete - O(m + k)
    void autocomplete(string prefix, vector<string>& results) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!curr->children[index]) return;
            curr = curr->children[index];
        }
        collectWords(curr, prefix, results);
    }

    void collectWords(TrieNode* node, string prefix, vector<string>& results) {
        if (!node) return;
        if (node->isEndOfWord) results.push_back(prefix);
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                collectWords(node->children[i], prefix + char('a' + i), results);
            }
        }
    }

    // Count words with prefix
    int countWordsWithPrefix(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!curr->children[index]) return 0;
            curr = curr->children[index];
        }
        return countWords(curr);
    }

    int countWords(TrieNode* node) {
        if (!node) return 0;
        int count = node->wordCount;
        for (int i = 0; i < 26; i++) {
            count += countWords(node->children[i]);
        }
        return count;
    }
};
```

## Example Usage

```cpp
int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("banana");

    cout << "Search 'apple': " << trie.search("apple") << endl;  // 1
    cout << "Search 'app': " << trie.search("app") << endl;      // 1
    cout << "Search 'appl': " << trie.search("appl") << endl;    // 0

    cout << "Starts with 'app': " << trie.startsWith("app") << endl;  // 1

    cout << "Words with prefix 'app': " << trie.countWordsWithPrefix("app") << endl;  // 4

    vector<string> suggestions;
    trie.autocomplete("app", suggestions);
    cout << "Autocomplete 'app': ";
    for (string& s : suggestions) cout << s << " ";  // app apple application apply
    cout << endl;

    trie.deleteWord("app");
    cout << "After delete, search 'app': " << trie.search("app") << endl;  // 0
    cout << "Search 'apple': " << trie.search("apple") << endl;  // 1

    return 0;
}
```
