#include <bits/stdc++.h>
using namespace std;

// Doubly linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Function to insert node at end
void insertEnd(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to find pairs with given sum
vector<pair<int, int>> findPairsWithGivenSum(Node* head, int target) {
    Node* start = head;
    Node* end = head;
    int startBalance = 0;
    int endBalance = 0;

    // Move 'end' to the last node
    while (end->next != nullptr) {
        end = end->next;
        endBalance++;
    }

    vector<pair<int, int>> result;
    while (startBalance < endBalance) {
        int sum = start->data + end->data;
        if (sum > target) {
            end = end->prev;
            endBalance--;
        } else if (sum < target) {
            start = start->next;
            startBalance++;
        } else {
            result.push_back({start->data, end->data});
            start = start->next;
            startBalance++;
            end = end->prev;
            endBalance--;
        }
    }
    return result;
}

int main() {
    Node* head = nullptr;
    int n, target;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        insertEnd(head, x);
    }

    cout << "Enter target sum: ";
    cin >> target;

    vector<pair<int, int>> ans = findPairsWithGivenSum(head, target);

    if (ans.empty()) {
        cout << "No pairs found.\n";
    } else {
        cout << "Pairs with sum " << target << ":\n";
        for (auto& p : ans) {
            cout << "(" << p.first << ", " << p.second << ")\n";
        }
    }

    return 0;
}
