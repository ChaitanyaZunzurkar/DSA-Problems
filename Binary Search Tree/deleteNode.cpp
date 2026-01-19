#include <iostream>
using namespace std;

/*
==========================
INTUITION (IMPORTANT)
==========================

A Binary Search Tree (BST) has these properties:
1. Left subtree values < node value
2. Right subtree values > node value

While deleting a node from a BST, we must ensure
these properties remain valid.

There are 3 cases when deleting a node:

Case 1: Node has no left child
→ Replace node with its right child

Case 2: Node has no right child
→ Replace node with its left child

Case 3: Node has two children
→ Find the inorder successor (minimum value in right subtree)
→ Copy its value to the current node
→ Delete the duplicate successor from the right subtree

Why inorder successor?
- It is the smallest value greater than the current node
- It preserves BST ordering
*/

// Definition of a BST node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

// Function to insert a value into BST
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }

    return root;
}

// Function to delete a node from BST
TreeNode* deleteNode(TreeNode* root, int key) {
    // Base case: empty tree
    if (root == nullptr) {
        return root;
    }

    // If the node to delete is found
    if (root->val == key) {

        // Case 1: no left child
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2: no right child
        if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: two children
        // Find inorder successor (minimum in right subtree)
        TreeNode* curr = root->right;
        while (curr->left != nullptr) {
            curr = curr->left;
        }

        // Copy successor value to current node
        root->val = curr->val;

        // Delete the duplicate successor node
        root->right = deleteNode(root->right, curr->val);
    }
    // If key is smaller, go left
    else if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    // If key is greater, go right
    else {
        root->right = deleteNode(root->right, key);
    }

    return root;
}

// Inorder traversal (prints BST in sorted order)
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

int main() {
    TreeNode* root = nullptr;
    int n, value, key;

    cout << "Enter number of elements to insert in BST: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insertIntoBST(root, value);
    }

    cout << "\nInorder traversal before deletion: ";
    inorderTraversal(root);
    cout << endl;

    cout << "\nEnter value to delete: ";
    cin >> key;

    root = deleteNode(root, key);

    cout << "\nInorder traversal after deletion: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
