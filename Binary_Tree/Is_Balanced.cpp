#include <bits/stdc++.h>
using namespace std;

/*
    Definition of Binary Tree Node
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
    FUNCTION TO BUILD TREE USING LEVEL ORDER INPUT

    INTUITION:
    - We read values level by level
    - -1 represents a NULL child
    - Queue helps us attach children correctly
*/
TreeNode* buildTree() {
    int val;
    cin >> val;

    // If first value is -1, tree is empty
    if(val == -1) return NULL;

    TreeNode* root = new TreeNode(val);
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        int leftVal, rightVal;
        cin >> leftVal;

        if(leftVal != -1) {
            curr->left = new TreeNode(leftVal);
            q.push(curr->left);
        }

        cin >> rightVal;
        if(rightVal != -1) {
            curr->right = new TreeNode(rightVal);
            q.push(curr->right);
        }
    }

    return root;
}

/*
    FUNCTION TO CALCULATE HEIGHT OF A TREE

    INTUITION:
    - Height of empty tree = 0
    - Height of a node =
        1 + maximum height of its left or right subtree
*/
int height(TreeNode* root) {
    if(root == NULL) {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

/*
    FUNCTION TO CHECK IF TREE IS BALANCED

    INTUITION:
    - A tree is balanced if:
        1) Difference between left and right subtree heights ≤ 1
        2) Left subtree is balanced
        3) Right subtree is balanced
    - This condition must hold true for EVERY node
*/
bool isBalanced_brute(TreeNode* root) {
    if(root == NULL) return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Check balance condition at current node
    if(abs(leftHeight - rightHeight) > 1) {
        return false;
    }

    // Recursively check balance for left and right subtrees
    bool leftBalanced = isBalanced(root->left);
    bool rightBalanced = isBalanced(root->right);

    if(!leftBalanced || !rightBalanced) {
        return false;
    }

    return true;
}

int main() {
    /*
        INPUT FORMAT:
        - Enter tree in level order
        - Use -1 for NULL nodes

        Example:
        1 2 3 -1 -1 4 5
    */

    cout << "Enter tree nodes in level order (-1 for NULL):\n";
    TreeNode* root = buildTree();

    if(isBalanced_brute(root)) {
        cout << "The binary tree is BALANCED\n";
    } else {
        cout << "The binary tree is NOT BALANCED\n";
    }

    return 0;
}
