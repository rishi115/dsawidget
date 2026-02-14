# Binary Tree

A tree where each node has at most two children.

## Time Complexity

| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Traversal | O(n) | O(n) |
| Height | O(n) | O(n) |

## Implementation

```cpp
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;
    BinaryTree() : root(nullptr) {}

    // Insert level order
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!root) { root = newNode; return; }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front(); q.pop();
            if (!curr->left) { curr->left = newNode; return; }
            else q.push(curr->left);
            if (!curr->right) { curr->right = newNode; return; }
            else q.push(curr->right);
        }
    }

    // Inorder: Left -> Root -> Right
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Preorder: Root -> Left -> Right
    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Postorder: Left -> Right -> Root
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Level Order (BFS)
    void levelOrder() {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front(); q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    // Height
    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Count nodes
    int countNodes(Node* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    // Count leaf nodes
    int countLeaves(Node* node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    // Search
    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        return search(node->left, val) || search(node->right, val);
    }

    // Mirror tree
    void mirror(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    // Diameter (longest path)
    int diameter(Node* node, int& height) {
        if (!node) { height = 0; return 0; }
        int lh = 0, rh = 0;
        int ld = diameter(node->left, lh);
        int rd = diameter(node->right, rh);
        height = max(lh, rh) + 1;
        return max({lh + rh, ld, rd});
    }
};
```

## Example Usage

```cpp
int main() {
    BinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    /*
            1
           / \
          2   3
         / \ / \
        4  5 6  7
    */

    cout << "Inorder: ";
    tree.inorder(tree.root);     // 4 2 5 1 6 3 7

    cout << "\nPreorder: ";
    tree.preorder(tree.root);    // 1 2 4 5 3 6 7

    cout << "\nPostorder: ";
    tree.postorder(tree.root);   // 4 5 2 6 7 3 1

    cout << "\nLevel Order: ";
    tree.levelOrder();           // 1 2 3 4 5 6 7

    cout << "\nHeight: " << tree.height(tree.root);      // 3
    cout << "\nTotal nodes: " << tree.countNodes(tree.root);  // 7
    cout << "\nLeaf nodes: " << tree.countLeaves(tree.root);  // 4

    return 0;
}
```
