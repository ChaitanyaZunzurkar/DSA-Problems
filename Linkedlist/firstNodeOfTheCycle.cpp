#include <iostream>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* detectCycle(ListNode* head) {
    unordered_map<ListNode*, int> ump;
    ListNode* curr = head;

    while (curr != nullptr) {
        if (ump.find(curr) != ump.end()) {
            return curr;
        }
        ump[curr] = 1;
        curr = curr->next;
    }
    return nullptr;
}

ListNode *findStartNodeOfTheCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) {
            slow = head;
            while(slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return nullptr;
}

int main() {
    int n;
    cout << "Enter number of nodes in the linked list: ";
    cin >> n;

    if (n <= 0) {
        cout << "Empty list. No cycle." << endl;
        return 0;
    }

    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    cout << "Enter node values:" << endl;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int pos;
    cout << "Enter index (0-based) to create cycle (-1 for no cycle): ";
    cin >> pos;

    if (pos >= 0 && pos < n) {
        ListNode* cycleStart = head;
        for (int i = 0; i < pos; ++i) {
            cycleStart = cycleStart->next;
        }
        tail->next = cycleStart;
    }

    ListNode* result = findStartNodeOfTheCycle(head);

    if (result) {
        cout << "Cycle detected at node with value: " << result->val << endl;
    } else {
        cout << "No cycle detected." << endl;
    }

    return 0;
}
