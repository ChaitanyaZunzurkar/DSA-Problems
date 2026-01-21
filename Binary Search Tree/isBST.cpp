#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        /*
            Intuition:
            - For a Binary Search Tree (BST):
              * All values in the left subtree must be strictly smaller than the node
              * All values in the right subtree must be strictly greater than the node

            - We validate the tree by maintaining a valid range (min, max) for every node.
            - Initially, the range is (-infinity, +infinity).
            - For left child:
                max becomes current node's value
            - For right child:
                min becomes current node's value

            - If any node violates this range, the tree is NOT a valid BST.
        */

        return helper(root, LLONG_MIN, LLONG_MAX);
    }

    bool helper(TreeNode* root, long long mini, long long maxi) {
        // Base case: empty subtree is always valid
        if (root == nullptr) {
            return true;
        }

        // Current node must lie strictly between (mini, maxi)
        if (root->val <= mini || root->val >= maxi) {
            return false;
        }

        // Recursively validate:
        // 1. Left subtree with updated upper bound
        // 2. Right subtree with updated lower bound
        return helper(root->left, mini, root->val) &&
               helper(root->right, root->val, maxi);
    }
};

/* ===========================
   Driver Code
   =========================== */
int main() {
    /*
            5
           / \
          3   7
         / \   \
        2   4   8

        This is a valid BST
    */

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(8);

    Solution obj;
    cout << (obj.isValidBST(root) ? "Valid BST" : "Invalid BST") << endl;

    return 0;
}
