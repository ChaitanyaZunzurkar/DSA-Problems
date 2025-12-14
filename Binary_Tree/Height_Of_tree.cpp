#include <bits/stdc++.h>
using namespace std;

/*
    Definition of a Binary Tree Node
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
    - We use a queue to attach children level by level
    - For every node, we ask for its left and right child
    - If input is -1, that child is NULL
*/
TreeNode* buildTree() {
    int val;
    cin >> val;

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
    FUNCTION TO CALCULATE MAX DEPTH OF BINARY TREE

    INTUITION:
    - If tree is empty, depth is 0
    - For a node:
        1) Find depth of left subtree
        2) Find depth of right subtree
        3) Take the maximum of both
        4) Add 1 for the current node
*/
int maxDepth(TreeNode* root) {
    // Base case: empty tree
    if(root == NULL) {
        return 0;
    }

    // Recursive calls to left and right subtrees
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    // Current node adds 1 level
    return 1 + max(leftDepth, rightDepth);
}

int main() {
    /*
        INPUT INSTRUCTIONS:
        - Enter tree in level order
        - Use -1 for NULL nodes

        Example:
        1 2 3 -1 -1 4 5
    */

    cout << "Enter tree nodes in level order (-1 for NULL):\n";
    TreeNode* root = buildTree();

    int depth = maxDepth(root);

    cout << "Maximum Depth of Binary Tree: " << depth << endl;

    return 0;
}
