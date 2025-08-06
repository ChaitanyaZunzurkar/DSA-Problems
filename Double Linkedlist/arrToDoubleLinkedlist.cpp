#include <bits/stdc++.h>
using namespace std;

class Node {
    public :
        int val;
        Node * next;
        Node * back;

        Node (int val , Node * next , Node * back) {
            this->val = val;
            this->next = next;
            this->back = back;
        }

        Node (int val) {
            this->val = val;
            this->next = nullptr;
            this->back = nullptr;
        }
};

Node * arrToDoubleLinkedList(int arr[] , int n) {
    if (n == 0) return nullptr;
    Node * head = new Node(arr[0]);
    Node * prev = head;

    for(int i = 0; i < n; i++) {
        Node * temp = new Node(arr[i] , nullptr , prev);
        prev->next = temp;
        prev = temp;
    }

    return head;
}

void printDoubleLinkedlist(Node * head) {
    while(head != NULL) {
        cout << head->val << endl;
        head = head->next;
    }
    cout << endl;

    while(head != NULL) {
        cout << head->val << endl;
        head = head->back;
    }

}


int main()
{
    const int n = 7;
    int arr[] = {10 , 20 , 30 , 40 , 50 , 60 , 70};
    Node * root = arrToDoubleLinkedList(arr , n);
    printDoubleLinkedlist(root);
    return 0;
}