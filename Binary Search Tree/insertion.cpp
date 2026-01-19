#include <iostream>
using namespace std;

/*
Intuition:
-----------
A Binary Search Tree (BST) follows these rules:
1. Left subtree contains values smaller than the node.
2. Right subtree contains values greater than the node.
3. Both left and right subtrees are also BSTs.

To insert a value:
- If the tree is empty, create a new node.
- If the value is smaller than current node, go left.
- Otherwise, go right.
- Repeat this process recursively until an empty position is found.
*/

// Structure for a BST node
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
    // Base case: if tree (or subtree) is empty, create a new node
    if (root == nullptr) {
        return new TreeNode(val);
    }

    // If value is smaller, insert into left subtree
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    }
    // If value is greater or equal, insert into right subtree
    else {
        root->right = insertIntoBST(root->right, val);
    }

    // Return unchanged root pointer
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
    int n, value;

    cout << "Enter number of elements to insert: ";
    cin >> n;

    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insertIntoBST(root, value);
    }

    cout << "\nInorder traversal of BST (sorted order): ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
