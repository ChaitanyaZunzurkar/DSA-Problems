#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

// Function to segregate 0s, 1s, and 2s
Node* segregate(Node* head) {
    if (head == NULL || head->next == NULL) return head;

    int zeroCount = 0, oneCount = 0, twoCount = 0;
    Node* curr = head;

    // Count 0s, 1s, and 2s
    while (curr != NULL) {
        if (curr->data == 0) zeroCount++;
        else if (curr->data == 1) oneCount++;
        else twoCount++;
        curr = curr->next;
    }

    // Overwrite values
    curr = head;
    int i = 0;
    while (curr != NULL) {
        if (i < zeroCount)
            curr->data = 0;
        else if (i < zeroCount + oneCount)
            curr->data = 1;
        else
            curr->data = 2;
        i++;
        curr = curr->next;
    }

    return head;
}

// Function to create a list from user input
Node* createList(int n) {
    if (n <= 0) return NULL;
    int val;
    cin >> val;
    Node* head = new Node(val);
    Node* temp = head;
    for (int i = 1; i < n; ++i) {
        cin >> val;
        temp->next = new Node(val);
        temp = temp->next;
    }
    return head;
}

// Function to print the list
void printList(Node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Main
int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter " << n << " elements (only 0s, 1s, and 2s): ";
    Node* head = createList(n);

    head = segregate(head);

    cout << "Sorted linked list:\n";
    printList(head);

    return 0;
}
