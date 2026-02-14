# Stack (LIFO)

Last In First Out data structure.

## Time Complexity

| Operation | Time |
|-----------|------|
| Push | O(1) |
| Pop | O(1) |
| Peek/Top | O(1) |
| isEmpty | O(1) |
| Size | O(1) |

## Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Stack using Array
class StackArray {
private:
    int* arr;
    int top;
    int capacity;

public:
    StackArray(int cap = 100) {
        capacity = cap;
        arr = new int[capacity];
        top = -1;
    }

    ~StackArray() { delete[] arr; }

    void push(int val) {
        if (top == capacity - 1) return;
        arr[++top] = val;
    }

    int pop() {
        if (top == -1) return -1;
        return arr[top--];
    }

    int peek() {
        if (top == -1) return -1;
        return arr[top];
    }

    bool isEmpty() { return top == -1; }
    int size() { return top + 1; }
};

// Stack using Linked List
class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class StackLinkedList {
private:
    Node* top;
    int count;

public:
    StackLinkedList() : top(nullptr), count(0) {}

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    int pop() {
        if (!top) return -1;
        Node* temp = top;
        int val = top->data;
        top = top->next;
        delete temp;
        count--;
        return val;
    }

    int peek() { return top ? top->data : -1; }
    bool isEmpty() { return top == nullptr; }
    int size() { return count; }
};
```

## Applications

### 1. Balanced Parentheses

```cpp
bool isBalanced(string expr) {
    StackArray stack;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.isEmpty()) return false;
            char top = stack.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
        }
    }
    return stack.isEmpty();
}
```

### 2. Evaluate Postfix Expression

```cpp
int evaluatePostfix(string expr) {
    StackArray stack;
    for (char c : expr) {
        if (isdigit(c)) {
            stack.push(c - '0');
        } else {
            int b = stack.pop();
            int a = stack.pop();
            switch (c) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }
    return stack.pop();
}
```

### 3. Next Greater Element

```cpp
void nextGreaterElement(int arr[], int n) {
    StackArray stack;
    vector<int> result(n, -1);
    for (int i = n - 1; i >= 0; i--) {
        while (!stack.isEmpty() && stack.peek() <= arr[i])
            stack.pop();
        if (!stack.isEmpty()) result[i] = stack.peek();
        stack.push(arr[i]);
    }
}
```

### 4. Min Stack - O(1) getMin

```cpp
class MinStack {
private:
    StackArray mainStack;
    StackArray minStack;

public:
    void push(int val) {
        mainStack.push(val);
        if (minStack.isEmpty() || val <= minStack.peek())
            minStack.push(val);
    }

    int pop() {
        int val = mainStack.pop();
        if (val == minStack.peek()) minStack.pop();
        return val;
    }

    int getMin() { return minStack.peek(); }
    int top() { return mainStack.peek(); }
};
```

## Example Usage

```cpp
int main() {
    StackArray stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top: " << stack.peek() << endl;  // 30
    cout << "Pop: " << stack.pop() << endl;   // 30
    cout << "Top: " << stack.peek() << endl;  // 20

    // Balanced parentheses
    cout << isBalanced("({[]})") << endl;  // true
    cout << isBalanced("({[})") << endl;   // false

    // Postfix evaluation
    cout << evaluatePostfix("23*5+") << endl;  // 11

    return 0;
}
```
