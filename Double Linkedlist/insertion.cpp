#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* back;

    Node(int val, Node* next, Node* back) {
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

Node* arrToDoubleLinkedList(int arr[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* prev = head;

    for (int i = 1; i < n; i++) {
        Node* temp = new Node(arr[i], nullptr, prev);
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

Node* insertAtHead(Node* head, int val) {
    Node* newNode = new Node(val, head, nullptr);
    if (head != nullptr) {
        head->back = newNode;
    }
    return newNode; 
}

Node* insertAtTail(Node* head, int val) {
    if (head == nullptr) {
        return new Node(val);
    }
    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    Node* newNode = new Node(val, nullptr, tail);
    tail->next = newNode;
    return head;
}

Node* insertAtKthNode(Node* head, int k, int val) {
    if (k <= 1 || head == nullptr) {
        return insertAtHead(head, val);
    }

    Node* curr = head;
    int count = 1;
    while (curr != nullptr && count < k - 1) {
        curr = curr->next;
        count++;
    }

    if (curr == nullptr || curr->next == nullptr) {
        return insertAtTail(head, val); 
    }

    Node* front = curr->next;
    Node* newNode = new Node(val, front, curr);

    curr->next = newNode;
    if (front != nullptr) {
        front->back = newNode;
    }

    return head;
}

int main() {
    const int n = 12;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    Node* root = arrToDoubleLinkedList(arr, n);
    printDoubleLinkedlist(root);

    cout << "\nInsertion at head (value 5)" << endl;
    root = insertAtHead(root, 5);
    printDoubleLinkedlist(root);

    cout << "\nInsertion at tail (value 130)" << endl;
    root = insertAtTail(root, 130);
    printDoubleLinkedlist(root);

    cout << "\nInsertion at 4th position (value 25)" << endl;
    root = insertAtKthNode(root, 4, 25);
    printDoubleLinkedlist(root);

    return 0;
}
