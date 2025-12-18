#include <iostream>
using namespace std;

/*
 Definition for singly-linked list.
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
 Intuition:
 - Since the list is sorted, duplicates are adjacent.
 - curr1 keeps track of the last unique node.
 - curr2 moves ahead to skip all nodes having the same value as curr1.
 - Once curr2 reaches a different value (or NULL),
   we connect curr1->next to curr2.
 - This removes duplicates in-place with O(n) time and O(1) space.
*/
ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode* curr1 = head;
    ListNode* curr2 = head->next;

    while (curr1 != nullptr && curr2 != nullptr) {

        // Skip all nodes having the same value as curr1
        while (curr2 != nullptr && curr1->val == curr2->val) {
            curr2 = curr2->next;
        }

        // Link curr1 to the next distinct node
        curr1->next = curr2;

        // Move curr1 forward
        curr1 = curr1->next;

        // Move curr2 forward safely
        if (curr2 != nullptr)
            curr2 = curr2->next;
    }

    return head;
}

// Helper function to print the linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Driver code
int main() {
    // Creating list: 1 -> 1 -> 2 -> 3 -> 3
    ListNode* head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(3);

    cout << "Original list: ";
    printList(head);

    head = deleteDuplicates(head);

    cout << "After removing duplicates: ";
    printList(head);

    return 0;
}
