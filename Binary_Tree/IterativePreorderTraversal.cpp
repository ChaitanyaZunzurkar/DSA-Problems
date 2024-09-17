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

vector<int> iterativePreorder(Node * root) {
    vector<int> result;
    if(root == nullptr) return result;

    stack<Node*> st;
    st.push(root);

    while(!st.empty()) {      
        Node * node = st.top();
        st.pop();
        result.push_back(node->data);

        if(node->right != nullptr) {
            st.push(node->right);
        } 
        if(node->left != nullptr) {
            st.push(node->left);
        }
    }
    return result;
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

    vector<int> result = iterativePreorder(root);
    for(int val : result) {
        cout << val << " ";
    }
    return 0;
}