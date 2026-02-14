#include <iostream>
using namespace std;

// Queue using Array
class QueueArray {
private:
    int* arr;
    int front, rear;
    int capacity, count;

public:
    QueueArray(int cap = 100) {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~QueueArray() { delete[] arr; }

    // Enqueue - O(1)
    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        count++;
    }

    // Dequeue - O(1)
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        int val = arr[front];
        front = (front + 1) % capacity;
        count--;
        return val;
    }

    // Front - O(1)
    int getFront() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    // Rear - O(1)
    int getRear() {
        if (isEmpty()) return -1;
        return arr[rear];
    }

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
    int size() { return count; }

    void print() {
        cout << "Queue: ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }
};

// Queue using Linked List
class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class QueueLinkedList {
private:
    Node* front;
    Node* rear;
    int count;

public:
    QueueLinkedList() : front(nullptr), rear(nullptr), count(0) {}

    ~QueueLinkedList() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        Node* temp = front;
        int val = front->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        count--;
        return val;
    }

    int getFront() { return front ? front->data : -1; }
    int getRear() { return rear ? rear->data : -1; }
    bool isEmpty() { return front == nullptr; }
    int size() { return count; }
};

// Deque (Double-Ended Queue)
class Deque {
private:
    int* arr;
    int front, rear;
    int capacity, count;

public:
    Deque(int cap = 100) {
        capacity = cap;
        arr = new int[capacity];
        front = -1;
        rear = 0;
        count = 0;
    }

    void insertFront(int val) {
        if (count == capacity) return;
        if (front == -1) { front = rear = 0; }
        else { front = (front - 1 + capacity) % capacity; }
        arr[front] = val;
        count++;
    }

    void insertRear(int val) {
        if (count == capacity) return;
        if (front == -1) { front = rear = 0; }
        else { rear = (rear + 1) % capacity; }
        arr[rear] = val;
        count++;
    }

    int deleteFront() {
        if (isEmpty()) return -1;
        int val = arr[front];
        if (front == rear) { front = rear = -1; }
        else { front = (front + 1) % capacity; }
        count--;
        return val;
    }

    int deleteRear() {
        if (isEmpty()) return -1;
        int val = arr[rear];
        if (front == rear) { front = rear = -1; }
        else { rear = (rear - 1 + capacity) % capacity; }
        count--;
        return val;
    }

    int getFront() { return isEmpty() ? -1 : arr[front]; }
    int getRear() { return isEmpty() ? -1 : arr[rear]; }
    bool isEmpty() { return count == 0; }
    int size() { return count; }
};

int main() {
    cout << "=== Queue using Array ===\n";
    QueueArray q1;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    q1.print();
    cout << "Front: " << q1.getFront() << ", Rear: " << q1.getRear() << endl;
    cout << "Dequeue: " << q1.dequeue() << endl;
    q1.print();

    cout << "\n=== Queue using Linked List ===\n";
    QueueLinkedList q2;
    q2.enqueue(100);
    q2.enqueue(200);
    cout << "Front: " << q2.getFront() << endl;
    cout << "Dequeue: " << q2.dequeue() << endl;

    cout << "\n=== Deque ===\n";
    Deque dq;
    dq.insertRear(5);
    dq.insertRear(10);
    dq.insertFront(3);
    cout << "Front: " << dq.getFront() << ", Rear: " << dq.getRear() << endl;
    cout << "Delete Front: " << dq.deleteFront() << endl;
    cout << "Delete Rear: " << dq.deleteRear() << endl;

    return 0;
}
