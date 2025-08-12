#include <bits/stdc++.h>
using namespace std;

// Doubly linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int x) : data(x), next(nullptr), prev(nullptr) {}
};

// Insert node at end
void insertEnd(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Print list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

// Delete all occurrences of x
void deleteAllOccurOfX(Node** head_ref, int x) {
    Node* curr = *head_ref;

    while (curr != nullptr) {
        if (curr->data == x) {
            Node* temp = curr;

            if (curr->prev != nullptr) { // not head
                curr->prev->next = curr->next;
            } else { // head node
                *head_ref = curr->next;
            }

            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }

            curr = curr->next; // move before delete
            delete temp;
        } else {
            curr = curr->next;
        }
    }
}

int main() {
    Node* head = nullptr;
    int n, x;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        insertEnd(head, val);
    }

    cout << "Enter value to delete: ";
    cin >> x;

    cout << "Original list: ";
    printList(head);

    deleteAllOccurOfX(&head, x);

    cout << "Updated list: ";
    printList(head);

    return 0;
}
