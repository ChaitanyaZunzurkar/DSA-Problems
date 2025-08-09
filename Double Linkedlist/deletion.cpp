#include <bits/stdc++.h>
using namespace std;

class Node {
    public: 
        int val;
        Node * next;
        Node * back;

        Node(int val , Node * next , Node * back) {
            this->val = val;
            this->next = next;
            this->back = back;
        }

        Node(int val) {
            this->val = val;
            this->next = nullptr;
            this->back = nullptr;
        }
};

Node * arrToDoubleLinkedList(int arr[] , int n) {
    if (n == 0) return nullptr;
    Node * head = new Node(arr[0]);
    Node * prev = head;

    for(int i = 1; i < n; i++) {
        Node * temp = new Node(arr[i] , nullptr , prev);
        prev->next = temp;
        prev = temp;
    }

    return head;
}

void printDoubleLinkedlist(Node* head) {
    cout << "This is linked list traversed from the head" << endl;

    Node* tail = nullptr;
    while (head != NULL) {
        cout << head->val << " ";
        tail = head;           
        head = head->next;
    }
    cout << endl;

    cout << "This is linked list traversed from the tail" << endl;
    while (tail != NULL) {
        cout << tail->val << " ";
        tail = tail->back;
    }

    cout << endl;
}

Node * deleteionAtHead(Node * head) {
    if(head == NULL || head->next == nullptr) {
        return nullptr;
    } 

    Node * prev = head;
    head = head->next;

    head->back = nullptr;
    prev->next = nullptr;

    return head;
}

int main()
{
    const int n = 7;
    int arr[] = {10 , 20 , 30 , 40 , 50 , 60 , 70};
    Node * root = arrToDoubleLinkedList(arr , n);
    printDoubleLinkedlist(root);

    cout << endl;
    cout << "Deleteion of node at head." << endl;
    root = deleteionAtHead(root);
    printDoubleLinkedlist(root);
    return 0;
}