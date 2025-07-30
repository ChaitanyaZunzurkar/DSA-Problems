#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to insert node at end
void insertAtEnd(ListNode*& head, int val) {
    ListNode* newNode = new ListNode(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    ListNode* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
}

// Function to remove nth node from end
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr) return nullptr;

    int count = 0;
    ListNode* curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }

    if (count == 1 && n == 1) {
        delete head;
        return nullptr;
    }

    if (n == count) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    int i = 1;
    ListNode* temp = head;
    while (i < (count - n)) {
        temp = temp->next;
        i++;
    }
    ListNode* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;

    return head;
}

// Function to print the linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    ListNode* head = nullptr;
    int n, x, len;

    cout << "Enter number of elements in the list: ";
    cin >> len;

    cout << "Enter elements: ";
    for (int i = 0; i < len; ++i) {
        cin >> x;
        insertAtEnd(head, x);
    }

    cout << "Enter n (position from end to delete): ";
    cin >> n;

    head = removeNthFromEnd(head, n);

    cout << "List after deletion: ";
    printList(head);

    return 0;
}
