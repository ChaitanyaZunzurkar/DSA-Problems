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

int maxPath(TreeNode * root , int rightVal , int leftVal) {
    if(root == nullptr || root->val == rightVal || root->val == leftVal) return root->val;

    int lh = maxPath(root->left , rightVal , leftVal);
    int rh = maxPath(root->right , rightVal , leftVal);

    int maxPath = 0;
    maxPath = maxPath + lh + rh;
    return maxPath;
}

int main()
{
    TreeNode * root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    cout << maxPath(root , 4 , 7) << endl;
    return 0;
}