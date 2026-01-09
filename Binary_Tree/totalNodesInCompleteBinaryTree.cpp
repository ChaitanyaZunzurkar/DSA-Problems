#include <bits/stdc++.h>
using namespace std;

/*
 TreeNode structure for a binary tree
*/
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

/*
 DFS function to count nodes

 Intuition:
 - If the current node is NULL, there is nothing to count → return
 - Otherwise:
     1. Count the current node
     2. Recursively count nodes in the left subtree
     3. Recursively count nodes in the right subtree
*/
void dfs(TreeNode* node, int &count) {
    // Base case: if node is NULL, stop recursion
    if (node == nullptr) {
        return;
    }

    // Count the current node
    count++;

    // Visit left subtree
    dfs(node->left, count);

    // Visit right subtree
    dfs(node->right, count);
}

/*
 Function to count total nodes in the binary tree
*/
int countNodes(TreeNode* root) {
    int count = 0;
    dfs(root, count);
    return count;
}

/*
 Function to build a binary tree using level order input
 -1 represents NULL
*/
TreeNode* buildTree() {
    cout << "Enter root value (-1 for NULL): ";
    int val;
    cin >> val;

    if (val == -1) return NULL;

    TreeNode* root = new TreeNode(val);
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        int leftVal, rightVal;

        cout << "Enter left child of " << current->val << " (-1 for NULL): ";
        cin >> leftVal;
        if (leftVal != -1) {
            current->left = new TreeNode(leftVal);
            q.push(current->left);
        }

        cout << "Enter right child of " << current->val << " (-1 for NULL): ";
        cin >> rightVal;
        if (rightVal != -1) {
            current->right = new TreeNode(rightVal);
            q.push(current->right);
        }
    }

    return root;
}

/*
 Main function
*/
int main() {
    // Build the binary tree from user input
    TreeNode* root = buildTree();

    // Count nodes using DFS
    int result = countNodes(root);

    cout << "\nTotal number of nodes in the binary tree: " << result << endl;

    return 0;
}
