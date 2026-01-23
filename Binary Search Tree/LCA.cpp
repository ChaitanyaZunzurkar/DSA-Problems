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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        // Intuition:
        // If the current node is null, there is no tree to search,
        // so return nullptr.
        if (root == nullptr) {
            return nullptr;
        }

        // Store current node's value for easy comparison
        int curr = root->val;

        // Intuition:
        // In a Binary Search Tree:
        // - All values in the left subtree are smaller than curr
        // - All values in the right subtree are greater than curr
        //
        // If both p and q are greater than curr,
        // then both nodes must lie in the right subtree.
        // So the LCA must also be in the right subtree.
        if (p->val > curr && q->val > curr) {
            return lowestCommonAncestor(root->right, p, q);
        }

        // Intuition:
        // If both p and q are smaller than curr,
        // then both nodes must lie in the left subtree.
        // So the LCA must also be in the left subtree.
        if (p->val < curr && q->val < curr) {
            return lowestCommonAncestor(root->left, p, q);
        }

        // Intuition:
        // Otherwise, one of the following is true:
        // 1) p and q lie on different sides of the current node, or
        // 2) One of p or q is equal to the current node
        //
        // This means the current node is the first point where
        // the paths to p and q diverge.
        // Hence, this node is the Lowest Common Ancestor.
        return root;
    }
};
