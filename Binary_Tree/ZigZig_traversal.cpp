#include <bits/stdc++.h>
using namespace std;

/*
-------------------- INTUITION --------------------

We want to perform a level order traversal (BFS),
but with a twist:

• Level 0 → left to right
• Level 1 → right to left
• Level 2 → left to right
• and so on (zigzag pattern)

Key ideas:
1. Use a QUEUE for normal level order traversal.
2. Process the tree level by level.
3. For each level:
   - Create a vector of size = number of nodes at that level.
   - Decide the index where the node value should go:
       • If leftToRight → normal index (i)
       • If rightToLeft → reverse index (size - 1 - i)
4. After finishing one level, flip the direction.

This way:
• We still do BFS (simple & efficient)
• Zigzag order is achieved by smart indexing, not by reversing vectors
-------------------------------------------------
*/

// Definition of Binary Tree Node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

// Function to perform Zigzag Level Order Traversal
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;

    // If tree is empty, return empty result
    if (root == NULL) {
        return result;
    }

    // Queue for level order traversal
    queue<TreeNode*> q;
    q.push(root);

    // Flag to track traversal direction
    bool leftToRight = true;

    // Standard BFS loop
    while (!q.empty()) {
        int size = q.size();           // Number of nodes at current level
        vector<int> row(size);         // Store values of current level

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();

            // Decide index based on traversal direction
            int index;
            if (leftToRight) {
                index = i;
            } else {
                index = size - 1 - i;
            }

            row[index] = node->val;

            // Push children for next level
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        // Store the current level
        result.push_back(row);

        // Change direction for next level
        leftToRight = !leftToRight;
    }

    return result;
}

// Helper function to print the result
void printResult(vector<vector<int>> &result) {
    for (auto &level : result) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Driver code
int main() {
    /*
            1
           / \
          2   3
         / \   \
        4   5   6

    Zigzag Output:
    1
    3 2
    4 5 6
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    vector<vector<int>> result = zigzagLevelOrder(root);

    cout << "Zigzag Level Order Traversal:\n";
    printResult(result);

    return 0;
}
