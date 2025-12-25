#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        // If one list is empty, return the other
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        // Pointers to traverse both lists
        ListNode* curr1 = list1;
        ListNode* curr2 = list2;

        // 'result' will always point to the last node of merged list
        ListNode* result;

        /*
         * Step 1: Decide the head of merged list
         * Compare first nodes of both lists
         */
        if (curr1->val <= curr2->val) {
            result = curr1;
            curr1 = curr1->next;
        } else {
            result = curr2;
            curr2 = curr2->next;
        }

        // Store head pointer to return later
        ListNode* head = result;

        /*
         * Step 2: Merge while both lists have nodes
         * Always attach smaller node and move forward
         */
        while (curr1 != nullptr && curr2 != nullptr) {
            if (curr1->val <= curr2->val) {
                result->next = curr1;     // attach node
                curr1 = curr1->next;     // move list1
            } else {
                result->next = curr2;     // attach node
                curr2 = curr2->next;     // move list2
            }
            result = result->next;        // move merged list pointer
        }

        /*
         * Step 3: Attach remaining nodes
         * Only one of these will execute
         */
        if (curr1 != nullptr) {
            result->next = curr1;
        }

        if (curr2 != nullptr) {
            result->next = curr2;
        }

        // Return merged list head
        return head;
    }
};
