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

    // Destructor
    ~DoublyLinkedList() {
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

    // Insert at index - O(n)
    void insertAt(int index, int val) {
        if (index < 0 || index > size) {
            cout << "Invalid index\n";
            return;
        }
        if (index == 0) {
            insertAtHead(val);
            return;
        }
        if (index == size) {
            insertAtTail(val);
            return;
        }

        Node* newNode = new Node(val);
        Node* current;

        // Optimize: start from head or tail based on index
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }

        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }

    // Delete at head - O(1)
    void deleteAtHead() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    // Delete at tail - O(1)
    void deleteAtTail() {
        if (!tail) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    // Delete at index - O(n)
    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index\n";
            return;
        }
        if (index == 0) {
            deleteAtHead();
            return;
        }
        if (index == size - 1) {
            deleteAtTail();
            return;
        }

        Node* current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
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

    // Access by index - O(n/2) optimized
    int get(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index\n";
            return -1;
        }

        Node* current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }
        return current->data;
    }

    // Reverse - O(n)
    void reverse() {
        if (!head || !head->next) return;

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

    // Get size - O(1)
    int getSize() { return size; }

    // Check if empty - O(1)
    bool isEmpty() { return size == 0; }

    // Print forward
    void printForward() {
        cout << "Forward: NULL <-> ";
        Node* current = head;
        while (current) {
            cout << current->data;
            if (current->next) cout << " <-> ";
            current = current->next;
        }
        cout << " <-> NULL\n";
    }

    // Print backward
    void printBackward() {
        cout << "Backward: NULL <-> ";
        Node* current = tail;
        while (current) {
            cout << current->data;
            if (current->prev) cout << " <-> ";
            current = current->prev;
        }
        cout << " <-> NULL\n";
    }
};

int main() {
    DoublyLinkedList list;

    // Insert operations
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtHead(5);
    list.printForward();   // 5 <-> 10 <-> 20 <-> 30
    list.printBackward();  // 30 <-> 20 <-> 10 <-> 5

    // Insert at index
    list.insertAt(2, 15);
    list.printForward();  // 5 <-> 10 <-> 15 <-> 20 <-> 30

    // Access
    cout << "Element at index 2: " << list.get(2) << endl;  // 15
    cout << "Element at index 4: " << list.get(4) << endl;  // 30

    // Search
    cout << "Index of 20: " << list.search(20) << endl;  // 3

    // Delete operations
    list.deleteAtHead();
    list.printForward();  // 10 <-> 15 <-> 20 <-> 30

    list.deleteAtTail();
    list.printForward();  // 10 <-> 15 <-> 20

    list.deleteAt(1);
    list.printForward();  // 10 <-> 20

    // Reverse
    list.insertAtTail(30);
    list.insertAtTail(40);
    list.printForward();  // 10 <-> 20 <-> 30 <-> 40
    list.reverse();
    list.printForward();  // 40 <-> 30 <-> 20 <-> 10

    return 0;
}
