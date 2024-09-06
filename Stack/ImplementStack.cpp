#include <bits/stdc++.h>
using namespace std;

class Stack {
    const int size = 5;
    int top = -1;
    int arr[5];
    
    public :
        void push(int value);
        int pop();
        bool isEmpty();
        bool isFull();
        int peak(int index);
        void display(int n);
};

void Stack :: display(int n) {
    for(int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

int main()
{
    Stack obj1;
    obj1.push(4);
    obj1.display(1);
    obj1.push(5);
    obj1.display(2);
    obj1.push(7);
    obj1.display(3);
    obj1.pop();
    obj1.display(2);
    cout << obj1.peak(1);
    return 0;
}

void Stack::push(int value) {
    if(isFull()) {
        cout << "Stack Overflow" << endl;
    }
    else {
        top = top + 1;
        arr[top] = value;
    }
}

int Stack::pop() {
     if(isEmpty()) {
        cout << "Stack Underflow" << endl;
        return -1;
    }
    else {
        int popedValue = arr[top];
        top = top - 1;
        return popedValue;
    }
}

bool Stack::isEmpty() {
    return (top == -1);
} 

bool Stack::isFull() {
    return (top >= size-1);
}

int Stack:: peak(int index) {
    return arr[index];
}