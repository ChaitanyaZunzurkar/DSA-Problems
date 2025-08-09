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

Node * deletionAtHead(Node * head) {
    if(head == NULL || head->next == nullptr) {
        return nullptr;
    } 

    Node * prev = head;
    head = head->next;

    head->back = nullptr;
    prev->next = nullptr;

    delete prev;
    return head;
}

Node * deletionAtTail(Node * head) {
    if(head == NULL || head->next == nullptr) {
        return nullptr;
    } 

    Node * tail = head;
    while(tail != NULL && tail->next != nullptr) {
        tail = tail->next;
    }

    Node * prev = tail->back;
    tail->back = nullptr;
    prev->next = nullptr;

    delete tail;
    return head;
}

Node * deletionAtKthNode(Node * head , int k) {
    cout << "Deleteion of node at " << k <<  "th node." << endl;
    if(head == NULL || head->next == nullptr) {
        return nullptr;
    } 

    int i = 0;
    Node * curr = head;
    while(curr != NULL) {
        i++;
        if(i == k) {
            break;
        }
        curr = curr->next;
    }

    Node * prev = curr->back;
    Node * front  = curr->next;

    if(prev == NULL && front == NULL) {
        delete curr;
        return NULL;
    } 
    else if(prev == NULL) {
        return deletionAtHead(head);
    }
    else if(front == NULL) {
        return deletionAtTail(head);
    }

    prev->next = front;
    front->back = prev;

    curr->next = nullptr;
    curr->back = nullptr;

    delete curr;
    return head;
}

int main()
{
    const int n = 12;
    int arr[] = {10 , 20 , 30 , 40 , 50 , 60 , 70 , 80 , 90 , 100 , 110 , 120};
    Node * root = arrToDoubleLinkedList(arr , n);
    printDoubleLinkedlist(root);

    cout << endl;
    cout << "Deleteion of node at head." << endl;
    root = deletionAtHead(root);
    printDoubleLinkedlist(root);

    cout << endl;
    cout << "Deleteion of node at tail." << endl;
    root = deletionAtTail(root);
    printDoubleLinkedlist(root);

    cout << endl;
    root = deletionAtKthNode(root , 5);
    printDoubleLinkedlist(root);
    return 0;
}