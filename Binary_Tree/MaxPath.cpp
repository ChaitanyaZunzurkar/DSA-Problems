#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // This variable stores the maximum path sum found anywhere in the tree.
    // It is global so that all recursive calls can update it.
    int distance = INT_MIN;

    int calculate_distance(TreeNode *node) {
        if (node == NULL) {
            return 0;
        }

        // Step 1:
        // Recursively compute the maximum path sum coming from the left subtree.
        // If the contribution is negative, ignore it by taking max with 0.
        int leftDist = max(0, calculate_distance(node->left));

        // Step 2:
        // Recursively compute the maximum path sum coming from the right subtree.
        // Again, ignore negative contributions.
        int rightDist = max(0, calculate_distance(node->right));

        // Step 3:
        // The best path that passes THROUGH the current node is:
        // node value + best left contribution + best right contribution.
        // Update the global answer with this value.
        distance = max(distance, node->val + leftDist + rightDist);

        // Step 4:
        // Return the maximum path sum that can be EXTENDED to the parent.
        // Only one side (left or right) can be chosen, because a path cannot branch upward.
        return node->val + max(leftDist, rightDist);
    }

    int maxPathSum(TreeNode* root) {
        // Start DFS traversal from root.
        calculate_distance(root);

        // After traversal, 'distance' holds the maximum path sum.
        return distance;
    }
};

int main() {
    /*
        Example Tree:
               2
              /
            -1

        Expected Output: 2
    */

    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(-1);

    Solution sol;
    cout << "Maximum Path Sum: " << sol.maxPathSum(root) << endl;

    return 0;
}
