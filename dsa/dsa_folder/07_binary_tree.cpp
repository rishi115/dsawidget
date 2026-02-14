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
            Node* curr = q.front();
            q.pop();
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
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    // Height of tree
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

    // Iterative Inorder
    void inorderIterative() {
        stack<Node*> s;
        Node* curr = root;
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top(); s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }

    // Mirror tree
    void mirror(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    // Check if identical
    bool isIdentical(Node* a, Node* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->data == b->data && 
               isIdentical(a->left, b->left) && 
               isIdentical(a->right, b->right);
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
    tree.inorder(tree.root);
    cout << endl;  // 4 2 5 1 6 3 7

    cout << "Preorder: ";
    tree.preorder(tree.root);
    cout << endl;  // 1 2 4 5 3 6 7

    cout << "Postorder: ";
    tree.postorder(tree.root);
    cout << endl;  // 4 5 2 6 7 3 1

    cout << "Level Order: ";
    tree.levelOrder();
    cout << endl;  // 1 2 3 4 5 6 7

    cout << "Height: " << tree.height(tree.root) << endl;  // 3
    cout << "Total nodes: " << tree.countNodes(tree.root) << endl;  // 7
    cout << "Leaf nodes: " << tree.countLeaves(tree.root) << endl;  // 4
    cout << "Search 5: " << (tree.search(tree.root, 5) ? "Found" : "Not found") << endl;

    cout << "Inorder Iterative: ";
    tree.inorderIterative();
    cout << endl;

    return 0;
}
