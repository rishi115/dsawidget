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

    ~StackArray() {
        delete[] arr;
    }

    // Push - O(1)
    void push(int val) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    // Pop - O(1)
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    // Peek/Top - O(1)
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return -1;
        }
        return arr[top];
    }

    // isEmpty - O(1)
    bool isEmpty() { return top == -1; }

    // isFull - O(1)
    bool isFull() { return top == capacity - 1; }

    // Size - O(1)
    int size() { return top + 1; }

    // Print
    void print() {
        cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
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

    ~StackLinkedList() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Push - O(1)
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    // Pop - O(1)
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        Node* temp = top;
        int val = top->data;
        top = top->next;
        delete temp;
        count--;
        return val;
    }

    // Peek - O(1)
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return -1;
        }
        return top->data;
    }

    // isEmpty - O(1)
    bool isEmpty() { return top == nullptr; }

    // Size - O(1)
    int size() { return count; }
};

// ==================== STACK APPLICATIONS ====================

// 1. Check balanced parentheses
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
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}

// 2. Reverse a string
string reverseString(string str) {
    StackArray stack;
    for (char c : str) {
        stack.push(c);
    }
    string reversed = "";
    while (!stack.isEmpty()) {
        reversed += (char)stack.pop();
    }
    return reversed;
}

// 3. Evaluate postfix expression
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

// 4. Next Greater Element
void nextGreaterElement(int arr[], int n) {
    StackArray stack;
    vector<int> result(n, -1);

    for (int i = n - 1; i >= 0; i--) {
        while (!stack.isEmpty() && stack.peek() <= arr[i]) {
            stack.pop();
        }
        if (!stack.isEmpty()) {
            result[i] = stack.peek();
        }
        stack.push(arr[i]);
    }

    cout << "Next Greater Elements: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

// 5. Min Stack - O(1) for getMin
class MinStack {
private:
    StackArray mainStack;
    StackArray minStack;

public:
    MinStack() : mainStack(100), minStack(100) {}

    void push(int val) {
        mainStack.push(val);
        if (minStack.isEmpty() || val <= minStack.peek()) {
            minStack.push(val);
        }
    }

    int pop() {
        if (mainStack.isEmpty()) return -1;
        int val = mainStack.pop();
        if (val == minStack.peek()) {
            minStack.pop();
        }
        return val;
    }

    int getMin() {
        if (minStack.isEmpty()) return -1;
        return minStack.peek();
    }

    int top() {
        return mainStack.peek();
    }
};

int main() {
    cout << "=== Stack using Array ===\n";
    StackArray stack1;
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);
    stack1.print();  // 30 20 10

    cout << "Top: " << stack1.peek() << endl;  // 30
    cout << "Pop: " << stack1.pop() << endl;   // 30
    stack1.print();  // 20 10

    cout << "\n=== Stack using Linked List ===\n";
    StackLinkedList stack2;
    stack2.push(100);
    stack2.push(200);
    stack2.push(300);
    cout << "Top: " << stack2.peek() << endl;  // 300
    cout << "Pop: " << stack2.pop() << endl;   // 300
    cout << "Size: " << stack2.size() << endl; // 2

    cout << "\n=== Applications ===\n";

    // Balanced parentheses
    cout << "Is '({[]})' balanced? " << (isBalanced("({[]})") ? "Yes" : "No") << endl;  // Yes
    cout << "Is '({[})' balanced? " << (isBalanced("({[})") ? "Yes" : "No") << endl;    // No

    // Reverse string
    cout << "Reverse of 'Hello': " << reverseString("Hello") << endl;  // olleH

    // Evaluate postfix
    cout << "Postfix '23*5+': " << evaluatePostfix("23*5+") << endl;  // 11

    // Next greater element
    int arr[] = {4, 5, 2, 25};
    nextGreaterElement(arr, 4);  // 5 25 25 -1

    // Min Stack
    cout << "\n=== Min Stack ===\n";
    MinStack minStack;
    minStack.push(5);
    minStack.push(3);
    minStack.push(7);
    minStack.push(2);
    cout << "Min: " << minStack.getMin() << endl;  // 2
    minStack.pop();
    cout << "Min after pop: " << minStack.getMin() << endl;  // 3

    return 0;
}
