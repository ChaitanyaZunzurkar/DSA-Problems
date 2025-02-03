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

Node * deletionAtTheHead(Node * head) {
    if(head == nullptr) return nullptr;
    Node * temp = head;
    head = head->next;
    delete temp;
    return head;
}

Node * deletionAtEnd(Node * head) {
    if(head == nullptr) return nullptr;

    Node * curr = head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }    

    delete curr->next;
    curr->next = nullptr;
    return head;
}

Node * deletionAtKthPosition(Node * head , int k) {
    if(head == nullptr) return nullptr;
    if(k == 1) {
        Node * temp = head;
        head = head -> next;
        delete temp;
        return head;
    }

    int i = 0;
    Node * curr = head;
    while(curr != nullptr && i < k-1) {
        curr = curr->next;
    }

    if(curr == nullptr || curr->next == nullptr){
        return head;
    }
    Node * temp = curr->next;
    curr->next = curr->next->next;
    curr->next = temp->next;

    delete temp;
    return head;
}

int main()
{
    const int n = 7;
    int arr[] = {10 , 20 , 30 , 40 , 50 , 60 , 70};
    Node * root = arrToLinkedList(arr , n);
    printLinkedlist(root);
    root = deletionAtTheHead(root);
    printLinkedlist(root);
    root = deletionAtEnd(root);
    printLinkedlist(root);
    root = deletionAtKthPosition(root, 3);
    printLinkedlist(root);
    return 0;
}