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

        Node (int val , Node * next) {
            this->val = val;
            this->next = next;
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

// My approuch 
Node * addTwoLinkedlist_MyApprouch(Node * l1 , Node * l2) {
    Node * temp1 = l1;
    Node * temp2 = l2;
    Node * result = new Node(-1);
    int carry = 0;

    Node * curr = result;
    while(temp1 != NULL || temp2 != NULL) {
        int val = temp1->val + temp2->val + carry;

        if(val > 9) {
            carry = val / 10;
            val = val % 10;
        } else {
            carry = 0;  
        }

        curr->next = new Node(val);
        curr = curr->next;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    while(temp1 != NULL) {
        int val = temp1->val + carry;

        if(val > 9) {
            carry = val / 10;
            val = val % 10;
        }

        curr->next = new Node(val);
        curr = curr->next;

        temp1 = temp1->next;
    }

    while(temp2 != NULL) {
        int val = temp2->val + carry;

        if(val > 9) {
            carry = val / 10;
            val = val % 10;
        }

        curr->next = new Node(val);
        curr = curr->next;

        temp2 = temp2->next;
    }

    if (carry > 0) {
        curr->next = new Node(carry);
    }

    return result->next;
}

// Method 2
Node * addTwoLinkedlist(Node * l1 , Node * l2) {
    Node * temp1 = l1;
    Node * temp2 = l2;
    Node * result = new Node(-1);
    int carry = 0;

    Node * curr = result;
    int sum = 0;
    while(temp1 != NULL || temp2 != NULL) {
        int sum = carry;
        if(temp1) {
            sum = sum + temp1->val;
        }

        if(temp2) {
            sum = sum + temp1->val;
        }

        result = new Node(sum % 10);
        carry = sum / 10;

        curr->next = result;
        curr = curr->next;

        if(temp1) {
            temp1 = temp1->next;
        }

        if(temp2) {
            temp2 = temp2->next;
        }
    }

    if(carry) {
        result = new Node(carry);
        curr->next = result;
    }

    return result->next;
}

int main()
{
    const int n1 = 3;
    const int n2 = 3;

    int arr1[] = {9, 9, 9};
    int arr2[] = {9, 9, 9};

    Node *l1 = arrToLinkedList(arr1, n1);
    Node *l2 = arrToLinkedList(arr2, n2);

    cout << "List 1: ";
    printLinkedlist(l1);

    cout << "List 2: ";
    printLinkedlist(l2);

    Node *sum = addTwoLinkedlist(l1, l2);

    cout << "Sum List: ";
    printLinkedlist(sum);

    return 0;
}
