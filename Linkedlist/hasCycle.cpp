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

bool hasCycle(Node *head) {
    if (!head || !head->next) return false;
    Node* slow = head;
    Node* fast = head->next;

    while (slow != fast) {
        if (!fast || !fast->next) return false;
        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}

int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    if (hasCycle(head)) {
        cout << "Cycle detected!" << endl;
    } else {
        cout << "No cycle found." << endl;
    }

    return 0;
}