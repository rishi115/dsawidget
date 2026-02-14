# Singly Linked List

A linear data structure where elements are stored in nodes, each pointing to the next.

## Time Complexity

| Operation | Time |
|-----------|------|
| Insert at head | O(1) |
| Insert at tail | O(1)* |
| Insert at index | O(n) |
| Delete at head | O(1) |
| Delete at tail | O(n) |
| Delete at index | O(n) |
| Search | O(n) |
| Access by index | O(n) |
| Reverse | O(n) |

*With tail pointer

## Implementation

```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~SinglyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Insert at head - O(1)
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    // Insert at tail - O(1) with tail pointer
    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Insert at index - O(n)
    void insertAt(int index, int val) {
        if (index < 0 || index > size) return;
        if (index == 0) { insertAtHead(val); return; }
        if (index == size) { insertAtTail(val); return; }

        Node* newNode = new Node(val);
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    // Delete at head - O(1)
    void deleteAtHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        size--;
    }

    // Delete at tail - O(n)
    void deleteAtTail() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            size--;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
    }

    // Search - O(n)
    int search(int val) {
        Node* current = head;
        int index = 0;
        while (current) {
            if (current->data == val) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    // Access by index - O(n)
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Reverse - O(n)
    void reverse() {
        if (!head || !head->next) return;
        tail = head;
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    // Detect cycle - O(n) Floyd's algorithm
    bool hasCycle() {
        if (!head) return false;
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    // Find middle - O(n)
    int findMiddle() {
        if (!head) return -1;
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }

    // Get Nth from end - O(n)
    int getNthFromEnd(int n) {
        if (n <= 0 || n > size) return -1;
        Node* first = head;
        Node* second = head;
        for (int i = 0; i < n; i++) first = first->next;
        while (first) {
            first = first->next;
            second = second->next;
        }
        return second->data;
    }

    int getSize() { return size; }
    bool isEmpty() { return size == 0; }

    void print() {
        cout << "List: ";
        Node* current = head;
        while (current) {
            cout << current->data;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << " -> NULL\n";
    }
};
```

## Example Usage

```cpp
int main() {
    SinglyLinkedList list;

    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtHead(5);
    list.print();  // 5 -> 10 -> 20 -> 30 -> NULL

    list.insertAt(2, 15);
    list.print();  // 5 -> 10 -> 15 -> 20 -> 30 -> NULL

    cout << "Middle: " << list.findMiddle() << endl;  // 15
    cout << "2nd from end: " << list.getNthFromEnd(2) << endl;  // 20

    list.reverse();
    list.print();  // 30 -> 20 -> 15 -> 10 -> 5 -> NULL

    return 0;
}
```
