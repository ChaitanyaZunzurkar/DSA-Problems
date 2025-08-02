#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to find the middle of the list
ListNode* findMiddle(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Function to merge two sorted linked lists
ListNode* mergeTwoList(ListNode* list1, ListNode* list2) {
    ListNode* dummyNode = new ListNode(-1);
    ListNode* temp = dummyNode;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            temp->next = list1;
            list1 = list1->next;
        } else {
            temp->next = list2;
            list2 = list2->next;
        }
        temp = temp->next;
    }

    temp->next = (list1 != nullptr) ? list1 : list2;
    ListNode* result = dummyNode->next;
    delete dummyNode;  // clean up dummy node
    return result;
}

// Merge sort for linked list
ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode* middle = findMiddle(head);
    ListNode* rightHead = middle->next;
    middle->next = nullptr;

    ListNode* leftSorted = sortList(head);
    ListNode* rightSorted = sortList(rightHead);

    return mergeTwoList(leftSorted, rightSorted);
}

// Create list from user input
ListNode* createList(int n) {
    if (n <= 0) return nullptr;
    int val;
    cin >> val;
    ListNode* head = new ListNode(val);
    ListNode* temp = head;
    for (int i = 1; i < n; i++) {
        cin >> val;
        temp->next = new ListNode(val);
        temp = temp->next;
    }
    return head;
}

// Print the linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter the elements:\n";
    ListNode* head = createList(n);

    head = sortList(head);

    cout << "Sorted linked list:\n";
    printList(head);

    return 0;
}
