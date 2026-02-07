#include <bits/stdc++.h>
using namespace std;

class TreeNode {
    public :
        int val;
        TreeNode * left;
        TreeNode * right;

        TreeNode(int val) {
            this->val = val;
            this->left = nullptr;
            this->right = nullptr;
        }
};

int maxHeight(TreeNode * root) {
    if(root == nullptr) return 0;

    int lh = maxHeight(root->left);
    if(lh == -1) return -1;

    int rh = maxHeight(root->right);
    if(lh == -1) return -1;

    if(abs(lh - rh) > 1) return -1;
    return 1 + max(lh , rh);
}

bool isBalancedBinaryTree(TreeNode * node) {
    return maxHeight(node) != -1;
}

int main()
{
    TreeNode * root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    cout << isBalancedBinaryTree(root) << endl;
    return 0;
}