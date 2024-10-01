#include <bits/stdc++.h>
using namespace std;
#define MAX 10

class Node {
    public :
        int val;
        Node * next;

        Node (int val) {
            this->val = val;
            this->next = nullptr;
        }
};

int main()
{
    Node * root = new Node(12);

    Node * element2 = new Node(23);
    root->next = element2;

    Node * element3 = new Node(34);
    element2->next = element3;

    Node * curr = root;
    while (curr != nullptr) {
        cout << curr->val << " ";
        curr = curr->next;
    }    

    return 0;
}