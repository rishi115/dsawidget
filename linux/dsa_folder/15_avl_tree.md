# AVL Tree (Self-Balancing BST)

A BST that maintains balance by ensuring height difference between subtrees is at most 1.

## Time Complexity

| Operation | Time |
|-----------|------|
| Insert | O(log n) |
| Search | O(log n) |
| Delete | O(log n) |
| Rotation | O(1) |

## Implementation

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) { return node ? node->height : 0; }

    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    // Right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Insert with rebalancing
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        else
            return node;

        updateHeight(node);
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && val < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && val > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    // Delete with rebalancing
    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->data)
            node->left = deleteNode(node->left, val);
        else if (val > node->data)
            node->right = deleteNode(node->right, val);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) { temp = node; node = nullptr; }
                else { *node = *temp; }
                delete temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (!node) return nullptr;

        updateHeight(node);
        int balance = getBalance(node);

        // Rebalance
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    void deleteNode(int val) { root = deleteNode(root, val); }
    void inorder() { inorder(root); cout << endl; }
    int getHeight() { return height(root); }
};
```

## Example Usage

```cpp
int main() {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // Triggers left rotation
    tree.insert(40);
    tree.insert(50);  // Triggers left rotation
    tree.insert(25);  // Triggers right-left rotation

    cout << "Inorder: ";
    tree.inorder();  // 10 20 25 30 40 50

    cout << "Height: " << tree.getHeight() << endl;  // 3

    tree.deleteNode(30);
    cout << "After deleting 30: ";
    tree.inorder();  // 10 20 25 40 50

    return 0;
}
```
