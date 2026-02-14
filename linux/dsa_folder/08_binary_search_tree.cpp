#include <iostream>
#include <queue>
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

    // Insert - O(log n) avg, O(n) worst
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    // Search - O(log n) avg
    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    bool search(int val) {
        return search(root, val);
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
            // Node found
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
            // Two children: get inorder successor
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data);
        }
        return node;
    }

    void deleteNode(int val) {
        root = deleteNode(root, val);
    }

    // Inorder Successor
    Node* inorderSuccessor(Node* node, int val) {
        Node* successor = nullptr;
        Node* curr = node;
        while (curr) {
            if (val < curr->data) {
                successor = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return successor;
    }

    // Inorder Predecessor
    Node* inorderPredecessor(Node* node, int val) {
        Node* predecessor = nullptr;
        Node* curr = node;
        while (curr) {
            if (val > curr->data) {
                predecessor = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return predecessor;
    }

    // Validate BST
    bool isValidBST(Node* node, long minVal, long maxVal) {
        if (!node) return true;
        if (node->data <= minVal || node->data >= maxVal) return false;
        return isValidBST(node->left, minVal, node->data) &&
               isValidBST(node->right, node->data, maxVal);
    }

    bool isValidBST() {
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }

    // Inorder traversal
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void inorder() { inorder(root); }

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
};

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
    tree.inorder();
    cout << endl;  // 20 30 40 50 60 70 80

    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not found") << endl;
    cout << "Search 45: " << (tree.search(45) ? "Found" : "Not found") << endl;

    cout << "Min: " << tree.findMin(tree.root)->data << endl;  // 20
    cout << "Max: " << tree.findMax(tree.root)->data << endl;  // 80

    Node* succ = tree.inorderSuccessor(tree.root, 40);
    cout << "Successor of 40: " << (succ ? succ->data : -1) << endl;  // 50

    Node* pred = tree.inorderPredecessor(tree.root, 40);
    cout << "Predecessor of 40: " << (pred ? pred->data : -1) << endl;  // 30

    cout << "Is valid BST: " << (tree.isValidBST() ? "Yes" : "No") << endl;

    Node* ancestor = tree.lca(tree.root, 20, 40);
    cout << "LCA of 20 and 40: " << ancestor->data << endl;  // 30

    int k = 3;
    cout << "3rd smallest: " << tree.kthSmallest(tree.root, k) << endl;  // 40

    tree.deleteNode(30);
    cout << "After deleting 30: ";
    tree.inorder();
    cout << endl;  // 20 40 50 60 70 80

    return 0;
}
