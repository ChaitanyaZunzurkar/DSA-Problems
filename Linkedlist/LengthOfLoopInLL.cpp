#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

int countNodesinLoop(Node *head) {
    Node *slow = head;
    Node *fast = head;

    while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) { 
            int count = 1;
            Node *temp = slow;
            while (temp->next != slow) {
                count++;
                temp = temp->next;
            }
            return count;
        }
    }
    return 0; 
}

void insertNode(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void createLoop(Node* head, int pos) {
    if (pos == 0) return; 
    Node* loopNode = nullptr;
    Node* temp = head;
    int count = 1;
    while (temp->next != nullptr) {
        if (count == pos) {
            loopNode = temp;
        }
        temp = temp->next;
        count++;
    }
    temp->next = loopNode;
}

int main() {
    Node* head = nullptr;
    int n, val, loopPos;

    cout << "Enter number of nodes in the linked list: ";
    cin >> n;

    cout << "Enter " << n << " node values: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        insertNode(head, val);
    }

    cout << "Enter position to create loop (0 for no loop): ";
    cin >> loopPos;
    createLoop(head, loopPos);

    int result = countNodesinLoop(head);
    if (result == 0) {
        cout << "No loop detected in the linked list." << endl;
    } else {
        cout << "Loop detected! Number of nodes in loop: " << result << endl;
    }

    return 0;
}
