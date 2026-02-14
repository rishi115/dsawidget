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

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    // Right rotation - O(1)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation - O(1)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Insert - O(log n)
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        else
            return node;  // Duplicates not allowed

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

    // Delete - O(log n)
    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->data)
            node->left = deleteNode(node->left, val);
        else if (val > node->data)
            node->right = deleteNode(node->right, val);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
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

    bool search(Node* node, int val) {
        if (!node) return false;
        if (val == node->data) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << "(h=" << node->height << ") ";
        preorder(node->left);
        preorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    void deleteNode(int val) { root = deleteNode(root, val); }
    bool search(int val) { return search(root, val); }
    void inorder() { inorder(root); cout << endl; }
    void preorder() { preorder(root); cout << endl; }
    int getHeight() { return height(root); }
};

int main() {
    AVLTree tree;

    // Insert elements
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // Triggers left rotation
    tree.insert(40);
    tree.insert(50);  // Triggers left rotation
    tree.insert(25);  // Triggers right-left rotation

    cout << "Inorder: ";
    tree.inorder();  // 10 20 25 30 40 50

    cout << "Preorder (with heights): ";
    tree.preorder();

    cout << "Tree height: " << tree.getHeight() << endl;

    cout << "Search 25: " << (tree.search(25) ? "Found" : "Not found") << endl;
    cout << "Search 35: " << (tree.search(35) ? "Found" : "Not found") << endl;

    tree.deleteNode(30);
    cout << "After deleting 30:\n";
    cout << "Inorder: ";
    tree.inorder();

    return 0;
}
