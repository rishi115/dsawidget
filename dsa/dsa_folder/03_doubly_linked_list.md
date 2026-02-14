# Doubly Linked List

A linked list where each node has pointers to both next and previous nodes.

## Time Complexity

| Operation | Time |
|-----------|------|
| Insert at head | O(1) |
| Insert at tail | O(1) |
| Insert at index | O(n) |
| Delete at head | O(1) |
| Delete at tail | O(1) |
| Delete at index | O(n) |
| Search | O(n) |
| Access by index | O(n/2) |
| Traverse forward | O(n) |
| Traverse backward | O(n) |

## Implementation

```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Insert at head - O(1)
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Insert at tail - O(1)
    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Delete at head - O(1)
    void deleteAtHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }

    // Delete at tail - O(1)
    void deleteAtTail() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }

    // Access by index - O(n/2) optimized
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) current = current->next;
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) current = current->prev;
        }
        return current->data;
    }

    // Reverse - O(n)
    void reverse() {
        Node* current = head;
        Node* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }

    void printForward() {
        cout << "Forward: ";
        Node* current = head;
        while (current) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "NULL\n";
    }

    void printBackward() {
        cout << "Backward: ";
        Node* current = tail;
        while (current) {
            cout << current->data << " <-> ";
            current = current->prev;
        }
        cout << "NULL\n";
    }
};
```

## Example Usage

```cpp
int main() {
    DoublyLinkedList list;

    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtHead(5);
    list.printForward();   // 5 <-> 10 <-> 20 <-> 30 <-> NULL
    list.printBackward();  // 30 <-> 20 <-> 10 <-> 5 <-> NULL

    list.deleteAtHead();
    list.printForward();  // 10 <-> 20 <-> 30 <-> NULL

    list.deleteAtTail();
    list.printForward();  // 10 <-> 20 <-> NULL

    list.reverse();
    list.printForward();  // 20 <-> 10 <-> NULL

    return 0;
}
```
