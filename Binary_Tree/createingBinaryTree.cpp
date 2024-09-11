#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
    int data;
    Node *left;
    Node *right;

        Node(int val) {
            this->data = val;
            left = right = nullptr;
        }
};

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    cout << root->data << endl;
    cout << root->left->data << endl;
    cout << root->right->data << endl;
    return 0;
}