# Queue (FIFO)

First In First Out data structure.

## Time Complexity

| Operation | Time |
|-----------|------|
| Enqueue | O(1) |
| Dequeue | O(1) |
| Front | O(1) |
| Rear | O(1) |
| isEmpty | O(1) |

## Queue using Array (Circular)

```cpp
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

    void enqueue(int val) {
        if (count == capacity) return;
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        count++;
    }

    int dequeue() {
        if (count == 0) return -1;
        int val = arr[front];
        front = (front + 1) % capacity;
        count--;
        return val;
    }

    int getFront() { return count == 0 ? -1 : arr[front]; }
    int getRear() { return count == 0 ? -1 : arr[rear]; }
    bool isEmpty() { return count == 0; }
    int size() { return count; }
};
```

## Queue using Linked List

```cpp
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
        if (!front) return -1;
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
};
```

## Deque (Double-Ended Queue)

```cpp
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
        if (count == 0) return -1;
        int val = arr[front];
        if (front == rear) { front = rear = -1; }
        else { front = (front + 1) % capacity; }
        count--;
        return val;
    }

    int deleteRear() {
        if (count == 0) return -1;
        int val = arr[rear];
        if (front == rear) { front = rear = -1; }
        else { rear = (rear - 1 + capacity) % capacity; }
        count--;
        return val;
    }

    int getFront() { return count == 0 ? -1 : arr[front]; }
    int getRear() { return count == 0 ? -1 : arr[rear]; }
    bool isEmpty() { return count == 0; }
};
```

## Example Usage

```cpp
int main() {
    // Queue
    QueueArray q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Front: " << q.getFront() << endl;  // 10
    cout << "Dequeue: " << q.dequeue() << endl; // 10
    cout << "Front: " << q.getFront() << endl;  // 20

    // Deque
    Deque dq;
    dq.insertRear(5);
    dq.insertRear(10);
    dq.insertFront(3);
    cout << "Front: " << dq.getFront() << endl;  // 3
    cout << "Rear: " << dq.getRear() << endl;    // 10

    return 0;
}
```
