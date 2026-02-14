# Binary Search Tree (BST)

A binary tree where left child < parent < right child.

## Time Complexity

| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| FindMin | O(log n) | O(n) |
| FindMax | O(log n) | O(n) |

## Implementation

```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;
    BST() : root(nullptr) {}

    // Insert - O(log n) avg
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    void insert(int val) { root = insert(root, val); }

    // Search - O(log n) avg
    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    // Find Min - O(log n)
    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    // Find Max - O(log n)
    Node* findMax(Node* node) {
        while (node && node->right) node = node->right;
        return node;
    }

    // Delete - O(log n) avg
    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->data)
            node->left = deleteNode(node->left, val);
        else if (val > node->data)
            node->right = deleteNode(node->right, val);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data);
        }
        return node;
    }

    // Inorder Successor
    Node* inorderSuccessor(Node* node, int val) {
        Node* successor = nullptr;
        while (node) {
            if (val < node->data) {
                successor = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return successor;
    }

    // Validate BST
    bool isValidBST(Node* node, long minVal, long maxVal) {
        if (!node) return true;
        if (node->data <= minVal || node->data >= maxVal) return false;
        return isValidBST(node->left, minVal, node->data) &&
               isValidBST(node->right, node->data, maxVal);
    }

    // LCA (Lowest Common Ancestor)
    Node* lca(Node* node, int a, int b) {
        if (!node) return nullptr;
        if (a < node->data && b < node->data)
            return lca(node->left, a, b);
        if (a > node->data && b > node->data)
            return lca(node->right, a, b);
        return node;
    }

    // Kth smallest element
    int kthSmallest(Node* node, int& k) {
        if (!node) return -1;
        int left = kthSmallest(node->left, k);
        if (k == 0) return left;
        if (--k == 0) return node->data;
        return kthSmallest(node->right, k);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
};
```

## Example Usage

```cpp
int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    /*
            50
           /  \
          30   70
         / \   / \
        20 40 60 80
    */

    cout << "Inorder: ";
    tree.inorder(tree.root);  // 20 30 40 50 60 70 80

    cout << "\nSearch 40: " << tree.search(tree.root, 40);  // 1
    cout << "\nMin: " << tree.findMin(tree.root)->data;     // 20
    cout << "\nMax: " << tree.findMax(tree.root)->data;     // 80

    Node* lca = tree.lca(tree.root, 20, 40);
    cout << "\nLCA of 20 and 40: " << lca->data;  // 30

    tree.deleteNode(tree.root, 30);
    cout << "\nAfter deleting 30: ";
    tree.inorder(tree.root);  // 20 40 50 60 70 80

    return 0;
}
```
