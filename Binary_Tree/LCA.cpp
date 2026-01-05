#include <bits/stdc++.h>
using namespace std;

/**
 * Binary Tree Node definition
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Intuition:
 * We want to store the path from the root to a given target node.
 * While traversing:
 *  - Add the current node to the path
 *  - If this node is the target, we are done
 *  - Otherwise, search left and right subtrees
 *  - If target is not found, remove the node (backtracking)
 */
bool preorder(TreeNode* node, TreeNode* target, vector<TreeNode*>& path) {
    if (node == nullptr) {
        return false;
    }

    // Add current node to path
    path.push_back(node);

    // Target found
    if (node == target) {
        return true;
    }

    // Search left and right subtrees
    if (preorder(node->left, target, path) ||
        preorder(node->right, target, path)) {
        return true;
    }

    // Backtrack if target not found in this path
    path.pop_back();
    return false;
}

/**
 * Intuition:
 * 1. Find path from root to node p
 * 2. Find path from root to node q
 * 3. Compare both paths from the start
 * 4. The last common node is the Lowest Common Ancestor
 */
TreeNode* lowestCommonAncestor_brute(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> path_to_p;
    vector<TreeNode*> path_to_q;

    preorder(root, p, path_to_p);
    preorder(root, q, path_to_q);

    int i = 0;
    while (i < path_to_p.size() &&
           i < path_to_q.size() &&
           path_to_p[i] == path_to_q[i]) {
        i++;
    }

    // Last common node
    return path_to_p[i - 1];
}

TreeNode* lowestCommonAncestor_optimal(TreeNode* root, TreeNode* p, TreeNode* q) {

    // Intuition:
    // If we reach a null node, there is nothing to search here.
    // If the current node is either p or q, we have found one of the targets,
    // so return this node upward.
    if (root == nullptr || root == p || root == q) {
        return root;
    }

    // Intuition:
    // Recursively search for p and q in the left and right subtrees.
    // Each call returns:
    // - nullptr if neither p nor q is found in that subtree
    // - a non-null node if p or q (or their LCA) is found
    TreeNode* left  = lowestCommonAncestor_optimal(root->left,  p, q);
    TreeNode* right = lowestCommonAncestor_optimal(root->right, p, q);

    // Intuition:
    // If p and q are found in different subtrees,
    // left and right will both be non-null.
    // This means the current node is their lowest common ancestor.
    if (left == nullptr) {
        return right;
    } 
    else if (right == nullptr) {
        return left;
    } 
    else {
        // Both left and right are non-null → p and q split here
        return root;
    }
}


int main() {
    /**
     * Constructing the binary tree:
     *
     *          3
     *         / \
     *        5   1
     *       / \ / \
     *      6  2 0  8
     *        / \
     *       7   4
     */

    TreeNode* root = new TreeNode(3);

    root->left = new TreeNode(5);
    root->right = new TreeNode(1);

    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);

    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    // Nodes for which we want LCA
    TreeNode* p = root->left;                  // Node 5
    TreeNode* q = root->left->right->right;    // Node 4

    TreeNode* lca = lowestCommonAncestor_optimal(root, p, q);

    if (lca != nullptr) {
        cout << "Lowest Common Ancestor: " << lca->val << endl;
    }

    return 0;
}
