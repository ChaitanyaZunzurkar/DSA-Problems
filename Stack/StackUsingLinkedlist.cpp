#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int data;
        Node * next = nullptr;

        Node(int val) {
            this->data = val;
            next = nullptr;
        }
};

class Stack {
    public:
        Node * top;
        int size = 0;

        void push(int val) {
            Node * temp = new Node(val);
            temp->next = top;
            top = temp;
            size += 1;
        }

        int pop() {
            
        }
};

int main()
{
    
    return 0;
}