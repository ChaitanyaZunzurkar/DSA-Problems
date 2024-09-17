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

vector<vector<int>> levelWiseTraversal(Node * root) {
    vector<vector<int>> result;
    if(root == nullptr) return result;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();
        vector<int> levelWise;

        for(int i = 0; i < size; i++) {
            Node * node = q.front();
            q.pop();
            if(node->left != nullptr) q.push(node->left);
            if(node->right != nullptr) q.push(node->right);
            levelWise.push_back(node->data);
        }
        result.push_back(levelWise);
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

    vector<vector<int>> result = levelWiseTraversal(root);
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
    }
    return 0;
}