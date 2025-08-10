#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;

    ListNode* a = headA;
    ListNode* b = headB;

    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }

    return a;  
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

int main() {
    ListNode* intersect = new ListNode(8);
    intersect->next = new ListNode(10);

    ListNode* headA = new ListNode(3);
    headA->next = new ListNode(7);
    headA->next->next = intersect;

    ListNode* headB = new ListNode(99);
    headB->next = new ListNode(1);
    headB->next->next = intersect;

    cout << "List A: ";
    printList(headA);
    cout << "List B: ";
    printList(headB);

    ListNode* result = getIntersectionNode(headA, headB);

    if (result)
        cout << "Intersection at node with value: " << result->val << endl;
    else
        cout << "No intersection found." << endl;

    return 0;
}
