#include <bits/stdc++.h>
using namespace std;

class Node {
    public :
        int val;
        Node * next;

        Node (int val) {
            this->val = val;
            this->next = nullptr;
        }
};

Node * arrToLinkedList(int arr[] , int n) {
    if (n == 0) return nullptr;
    Node * head = new Node(arr[0]);
    Node * curr = head;

    for(int i = 1; i < n; i++) {
        Node * temp = new Node(arr[i]);
        curr->next = temp;
        curr = temp;
    }
    return head;
}

void printLinkedlist(Node * root) {
    while(root != NULL) {
        cout << root->val << " ";
        root = root->next;
    }
    cout << endl;
}

Node * insertionAtTheHead(Node * head , int val) {
    Node * temp = new Node(val);
    temp->next = head;
    head = temp;

    return head;
}

Node * insertionAtEnd(Node * head , int val) {
    if(head == nullptr) {
        return new Node(val); 
    }
    Node * curr = head;
    if(head == nullptr) {
        return curr;
    }
    Node * temp = new Node(val);
    while(curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = temp;

    return head;
}

Node * insertionAtKthPosition(Node * head , int val , int k) {
    if(k < 1) return head;

    if(k == 1) {
        Node * temp = new Node(val);
        temp->next = head;
        head = temp;
        return head;
    }
    Node * curr = head;
    int i = 1;
    while(curr != nullptr && i < k-1) {
        curr = curr->next;
        i++;
    }

    if(curr == nullptr) {
        return head;
    }
    Node * temp = new Node(val);
    temp->next = curr->next;
    curr->next = temp;

    return head;
}

int main()
{
    const int n = 7;
    int arr[] = {10 , 20 , 30 , 40 , 50 , 60 , 70};
    Node * root = arrToLinkedList(arr , n);
    printLinkedlist(root);
    root = insertionAtTheHead(root , 0);
    printLinkedlist(root);
    root = insertionAtEnd(root , 80);
    printLinkedlist(root);
    root = insertionAtKthPosition(root , 40 , 5);
    printLinkedlist(root);
    return 0;
}