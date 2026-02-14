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

    // Insert - O(m) where m = word length
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
            // Check if node has no children
            for (int i = 0; i < 26; i++) {
                if (curr->children[i]) return false;
            }
            return true;
        }

        int index = word[depth] - 'a';
        if (deleteWord(curr->children[index], word, depth + 1)) {
            delete curr->children[index];
            curr->children[index] = nullptr;
            // Check if current node should be deleted
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

    // Count words with prefix - O(m + k)
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

    // Get all words
    vector<string> getAllWords() {
        vector<string> results;
        collectWords(root, "", results);
        return results;
    }
};

int main() {
    Trie trie;

    // Insert words
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("banana");
    trie.insert("ball");

    // Search
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << endl;
    cout << "Search 'appl': " << (trie.search("appl") ? "Found" : "Not found") << endl;

    // Prefix check
    cout << "Starts with 'app': " << (trie.startsWith("app") ? "Yes" : "No") << endl;
    cout << "Starts with 'xyz': " << (trie.startsWith("xyz") ? "Yes" : "No") << endl;

    // Count words with prefix
    cout << "Words with prefix 'app': " << trie.countWordsWithPrefix("app") << endl;

    // Autocomplete
    vector<string> suggestions;
    trie.autocomplete("app", suggestions);
    cout << "Autocomplete 'app': ";
    for (string& s : suggestions) cout << s << " ";
    cout << endl;

    // Delete
    trie.deleteWord("app");
    cout << "After deleting 'app', search 'app': " << (trie.search("app") ? "Found" : "Not found") << endl;
    cout << "Search 'apple' still: " << (trie.search("apple") ? "Found" : "Not found") << endl;

    // All words
    cout << "All words: ";
    for (string& s : trie.getAllWords()) cout << s << " ";
    cout << endl;

    return 0;
}
