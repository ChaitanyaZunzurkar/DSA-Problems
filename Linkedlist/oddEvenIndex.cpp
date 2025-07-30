#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to rearrange nodes by odd and even indices
ListNode* oddEvenList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;

    while(even != nullptr && even->next != nullptr) {
        odd->next = even->next;
        odd = odd->next;

        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}

// Function to print the linked list
void printList(ListNode* head) {
    while(head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Main function to take input and execute the logic
int main() {
    int n;
    cout << "Enter the number of elements in the list: ";
    cin >> n;

    if(n == 0) {
        cout << "List is empty." << endl;
        return 0;
    }

    cout << "Enter the elements: ";
    int x;
    cin >> x;
    ListNode* head = new ListNode(x);
    ListNode* current = head;

    for(int i = 1; i < n; i++) {
        cin >> x;
        current->next = new ListNode(x);
        current = current->next;
    }

    head = oddEvenList(head);

    cout << "Rearranged list: ";
    printList(head);

    return 0;
}
