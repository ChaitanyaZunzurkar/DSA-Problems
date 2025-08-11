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

// Method 1
// By reversing the linkedlist 
Node* reverseLinkedList(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next; 
        curr->next = prev;   
        prev = curr;         
        curr = next;         
    }
    return prev; 
}


Node * addOneToLinkedlist(Node * head) {
    head = reverseLinkedList(head);
    Node * curr = head;
    int carry = 1;
    while(curr != NULL) {
        curr->val = curr->val + carry;
        if(curr->val < 10) {
            carry = 0;
            break;
        } 
        else {
            carry = 1;
            curr->val = 0;
        }
        curr = curr->next;
    }

    if(carry == 1) {
        Node * newNode = new Node(1);
        head = reverseLinkedList(head);
        newNode->next = head;
        head = newNode;
        return head;
    }

    head = reverseLinkedList(head);
    return head;
}

// Method 2
// using recursion 
int totalCarryEstimator(Node * temp) {
    if(temp == NULL) {
        return 1;
    }

    int carry = totalCarryEstimator(temp->next);
    temp->val = temp->val + carry;

    if(temp->val < 10) {
        return 0;
    }

    temp->val = 0;
    return 1;
}

Node * addOne(Node * head) {
    int  carry = totalCarryEstimator(head);
    if(carry == 1) {
        Node * newNode = new Node(1);
        newNode->next = head;
        return newNode;
    }

    return head;
}


int main()
{
    const int n = 3;
    int arr[] = {9 , 9 , 9};
    Node * root = arrToLinkedList(arr , n);
    printLinkedlist(root);
    
    // root = addOneToLinkedlist(root);
    // printLinkedlist(root);

    root = addOne(root);
    printLinkedlist(root);

    return 0;
}