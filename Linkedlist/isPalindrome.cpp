#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool isPalindrome(ListNode* head) {
    ListNode* curr = head;
    string result;

    while (curr != nullptr) {
        result += to_string(curr->val);
        curr = curr->next;
    }

    string temp = result;
    reverse(temp.begin(), temp.end());

    return result == temp;
}

int main() {
    int n;
    cout << "Enter number of elements in the linked list: ";
    cin >> n;

    if (n <= 0) {
        cout << "Empty list is considered a palindrome." << endl;
        return 0;
    }

    cout << "Enter " << n << " integers: ";
    int val;
    cin >> val;
    ListNode* head = new ListNode(val);
    ListNode* tail = head;

    for (int i = 1; i < n; ++i) {
        cin >> val;
        tail->next = new ListNode(val);
        tail = tail->next;
    }

    if (isPalindrome(head)) {
        cout << "The linked list is a palindrome." << endl;
    } else {
        cout << "The linked list is not a palindrome." << endl;
    }

    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
