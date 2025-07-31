#include <iostream>
using namespace std;

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to append a node to the end of the list
void appendNode(ListNode*& head, int val) {
    if (!head) {
        head = new ListNode(val);
        return;
    }
    ListNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new ListNode(val);
}

// Function to print the linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Function to find the middle of the linked list
ListNode* getMiddle(ListNode* head) {
    if (!head) return head;

    ListNode* slow = head;
    ListNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Function to merge two sorted lists
ListNode* merge(ListNode* left, ListNode* right) {
    if (!left) return right;
    if (!right) return left;

    ListNode* result = nullptr;

    if (left->val <= right->val) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// Merge Sort function
ListNode* mergeSort(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* middle = getMiddle(head);
    ListNode* nextToMiddle = middle->next;
    middle->next = nullptr;

    ListNode* left = mergeSort(head);
    ListNode* right = mergeSort(nextToMiddle);

    return merge(left, right);
}

// Main Function
int main() {
    ListNode* head = nullptr;
    int n, val;

    cout << "Enter the number of elements in the linked list: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        appendNode(head, val);
    }

    cout << "\nOriginal List: ";
    printList(head);

    head = mergeSort(head);

    cout << "\nSorted List: ";
    printList(head);

    return 0;
}
