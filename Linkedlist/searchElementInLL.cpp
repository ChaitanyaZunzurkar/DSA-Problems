#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int val;
        Node *next;

        Node(int val) {
            this->val = val;
            this->next = nullptr;
        }
};

Node * arrToLL(int arr[] , int n) {
    if(n == 0) return nullptr;
    Node * head = new Node(arr[0]);
    Node * curr = head;

    for(int i = 1; i < n; i++) {
        Node * temp = new Node(arr[i]);
        curr->next = temp;
        curr = temp;
    }

    return head;
}

int main()
{
    int n;
    cout << "Enter the size of the link list: ";
    cin >> n;

    Node * head = nullptr;
    Node * tail = nullptr;

    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        Node * temp = new Node(val);
        if(head == nullptr) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    int search;
    cout << "Enter the element you want to search : ";
    cin >> search;


    Node* curr = head;
    while (curr != nullptr) {
        if(curr->val == search) {
            cout << curr->val << " is present in LL" << endl;
            break;
        } 
        curr = curr->next;
    }

    if(curr == nullptr) {
        cout << search << " is not present in the LL" << endl;
    }
    cout << endl;
    return 0;
}