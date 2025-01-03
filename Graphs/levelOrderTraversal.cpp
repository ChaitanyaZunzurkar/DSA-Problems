#include <bits/stdc++.h>
using namespace std;

class TreeNode {
    public :
        int val;
        TreeNode * left;
        TreeNode * right;

        TreeNode(int data) {
            this->val = data;
            this->left = nullptr;
            this->right = nullptr;
        }
};

vector<vector<int>> levelOrdertraversal(TreeNode * root) {
    vector<vector<int>> result;
    if(root == NULL) return result;
    queue<TreeNode *> q;

    q.push(root);

    while(!q.empty()) {
        int size = q.size();
        vector<int> level;

        for(int i = 0; i < size; i++) {
            TreeNode * node = q.front();
            q.pop();

            if(node->left != NULL) {
                q.push(node->left);
            }
            if(node->left != NULL) {
                q.push(node->right);
            }

            level.push_back(node->val);
        }

        result.push_back(level);
    }

    return result;
}


int main() {
    TreeNode * root = new TreeNode(2);
    root->left = new TreeNode(4);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(6);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(3);

    vector<vector<int>> result = levelOrdertraversal(root);
    for(int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
    }

    return 0;
}