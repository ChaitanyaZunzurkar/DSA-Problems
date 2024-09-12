#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int data;
        Node * left;
        Node * right;

        Node(int val) {
            this->data = val;
            left = right = nullptr;
        }
};

void postOrderTraversal(Node * node) {
    if(node == nullptr) {
        return ;
    }

    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->data << " ";
}
int main()
{
    Node * root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->left = new Node(6);
    root->right->right = new Node(7);

    root->left->right->left = new Node(8);
    root->right->right->left = new Node(9);
    root->right->right->right = new Node(10);

    postOrderTraversal(root);
    return 0;
}