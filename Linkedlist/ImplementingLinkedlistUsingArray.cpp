#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int val;
        Node * next;

        Node(int val) {
            this->val = val;
            this->next = nullptr;
        }
};

Node * arrToLinkedList(int arr[] , int n) {
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
    while(root != nullptr) {
        cout << root->val << " ";
        root = root->next;
    }
    cout << endl;
}

int main()
{
    int n = 7;
    int arr[] = {10 , 20 , 30 , 40 , 50 , 60 , 70};
    Node * root = arrToLinkedList(arr , n);
    printLinkedlist(root);
    return 0;
}
