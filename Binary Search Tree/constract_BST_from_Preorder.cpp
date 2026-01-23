#include <iostream>
#include <vector>
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

/**
 * Insert a value into a BST.
 */
TreeNode* insertIntoBST(TreeNode* root, int val) {

    // Intuition:
    // If the current position is null, we have found the correct
    // place to insert the new value.
    if (root == nullptr) {
        return new TreeNode(val);
    }

    // Intuition:
    // Values smaller than the current node go to the left subtree.
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    }
    // Intuition:
    // Values greater than or equal to the current node
    // go to the right subtree.
    else {
        root->right = insertIntoBST(root->right, val);
    }

    // Intuition:
    // Return the root so parent nodes can reconnect properly.
    return root;
}

/**
 * Construct BST from preorder traversal (brute-force approach).
 */
TreeNode* bstFromPreorder_brute(vector<int>& preorder) {

    // Intuition:
    // The first element in preorder traversal is always the root.
    TreeNode* root = new TreeNode(preorder[0]);

    // Intuition:
    // Insert remaining elements one by one using BST insertion rules.
    for (int i = 1; i < preorder.size(); i++) {
        insertIntoBST(root, preorder[i]);
    }

    // Intuition:
    // Final tree represents the BST formed from the preorder traversal.
    return root;
}

/**
 * Construct BST from preorder traversal (Beter approach).
 * 1. We have a preorder traversal of BST 
 * 2. We can sort it and get inorder as well as we know inorder is always sorted in BST 
 * 3. Then we can constract a tree using inorder and preorder. 
 */

 /**
 * Construct BST from preorder traversal (Optimal approach).
 */


/**
 * Inorder traversal to verify BST correctness.
 */
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

int main() {

    // Example preorder traversal
    vector<int> preorder = {8, 5, 1, 7, 10, 12};

    // Build BST from preorder
    TreeNode* root = bstFromPreorder_brute(preorder);

    // Print inorder traversal (should be sorted for BST)
    cout << "Inorder Traversal of Constructed BST: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
