#include <iostream>
using namespace std;

class LinkedList {
public:
    class ListNode {
    public:
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* head;

    LinkedList() {
        head = nullptr;
    }

    void appendNode(int val) {
        if (!head) {
            head = new ListNode(val);
            return;
        }
        ListNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new ListNode(val);
    }

    void printList() {
        ListNode* temp = head;
        while (temp) {
            cout << temp->val;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    ListNode* findKthNode(ListNode* start, int k) {
        ListNode* temp = start;
        int i = 1;
        while (temp != NULL && i < k) {
            i++;
            temp = temp->next;
        }
        return temp;
    }

    ListNode* reverseLinkedList(ListNode* start) {
        ListNode* prev = NULL;
        ListNode* curr = start;
        ListNode* next = NULL;

        while (curr != NULL) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    void reverseKGroup(int k) {
        ListNode* temp = head;
        ListNode* kthNode;
        ListNode* prevNode = NULL;

        while (temp != NULL) {
            kthNode = findKthNode(temp, k);
            if (kthNode == NULL) {
                if (prevNode != NULL) {
                    prevNode->next = temp;
                    break;
                } else {
                    break;
                }
            }

            ListNode* nextNode = kthNode->next;
            kthNode->next = nullptr;

            reverseLinkedList(temp);

            if (temp == head) {
                head = kthNode;
            } else {
                prevNode->next = kthNode;
            }

            prevNode = temp;
            temp = nextNode;
        }
    }
};

int main() {
    LinkedList list;

    // Create linked list: 1 -> 2 -> 3 -> 4 -> 5
    for (int i = 1; i <= 5; i++) {
        list.appendNode(i);
    }

    cout << "Original list: ";
    list.printList();

    int k = 2;
    list.reverseKGroup(k);

    cout << "Reversed in groups of " << k << ": ";
    list.printList();

    return 0;
}
