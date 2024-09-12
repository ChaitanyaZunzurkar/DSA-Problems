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

void preOrderTraversal(Node * node) {
    if(node == nullptr) {
        return ;
    }

    cout << node->data << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
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

    preOrderTraversal(root);
    return 0;
}